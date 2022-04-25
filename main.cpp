#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
#include <pwd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct App {
    std::string name;
    std::string path;
    std::string wineprefix = std::string(getpwuid(getuid())->pw_dir) + "/.wine";
};

void setColor(SDL_Renderer* renderer, SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

pid_t startWineApp(const App& app){
    pid_t process = fork();

    if  (process == 0){
        std::string wine = "wine";
        std::string wineprefix = "WINEPREFIX=" + app.wineprefix;
        // Child
        char* args[] = {const_cast<char*>(wine.c_str()), const_cast<char*>(app.path.c_str()), nullptr};
        char* env[] = {const_cast<char*>(wineprefix.c_str()), nullptr};
        std::cout << "Executing ";

        for (int i = 0; args[i]; ++i){
            std::cout << args[i] << " ";
        }

        std::cout << " (env ";

        for (int i = 0; env[i]; ++i){
            std::cout << env[i] << " ";
        }

        std::cout << ")" << std::endl;
        execvpe(wine.c_str(), args, env);
    }

    // Parent
    return process;
}

int main(){
    std::vector<App> apps = {
            {"Wine Test", "../test/win.exe"},
            /*{"New App", "/path/to/executable", "/path/to/custom/wineprefix"}*/};

    pid_t currentPid = 0;
    App* currentApp = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Error while initializing SDL2.");
        return 1;
    }

    if (TTF_Init() != 0){
        std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
        exit(1);
    }

    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/adobe-source-code-pro/SourceCodePro-Black.otf", 12);

    if(!font) printf("TTF_OpenFont: %s\n", TTF_GetError());

    bool running = true;
    SDL_Event event;

    SDL_Rect windowSize{.x = 0, .y = 0, .w = 640, .h = 480};
    SDL_Window* window = SDL_CreateWindow("Plonk", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.w, windowSize.h, SDL_WINDOW_SHOWN);

    if (window == nullptr){
        printf("Could not create window.");
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_Color primary = {0, 0, 0, 255};
    SDL_Color secondary = {255, 0, 0, 255};
    SDL_Color textColor = {229, 107, 104};
    SDL_Color background = {50, 50, 50, 255};
    SDL_Color clear = {255, 255, 255, 255};

    int elementPerLine = 5;
    SDL_Rect rect{.w = windowSize.w / elementPerLine, .h = rect.w};

    while (running){
        SDL_GetWindowSize(window, &windowSize.w, &windowSize.h);

        setColor(renderer, clear);
        SDL_RenderClear(renderer);

        setColor(renderer, primary);

        if (currentPid != 0){
            int stat;
            waitpid(currentPid, &stat, WNOHANG);
            if (WIFEXITED(stat)){
                std::cout << "App " << currentApp->name << " (pid" << currentPid << ") has exited cleanly" << std::endl;
                currentPid = 0;
                currentApp = nullptr;
            }
        }

        if (currentPid == 0){
            // Draw stuff
            for (int i = 0; i < apps.size(); ++i){
                rect.x = rect.w * i % windowSize.w;
                rect.y = rect.w * i / windowSize.w;
                App& app = apps[i];
                SDL_RenderDrawRect(renderer, &rect);
                std::string text = app.name;
                SDL_Rect textRect;
                SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), textColor);
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

                SDL_FreeSurface(surface);

                TTF_SizeUTF8(font, text.c_str(), &textRect.w, &textRect.h);

                textRect.x = (int) round(rect.x + (rect.w - textRect.w) / 2.f);
                textRect.y = (int) round(rect.y + (rect.h - textRect.h) / 2.f);

                SDL_RenderCopy(renderer, texture, nullptr, &textRect);
                SDL_DestroyTexture(texture);
            }

        } else {
            std::string text = currentApp->name + " is currently running.";
            SDL_Rect textRect;
            SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), textColor);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

            SDL_FreeSurface(surface);

            TTF_SizeUTF8(font, text.c_str(), &textRect.w, &textRect.h);

            textRect.x = (windowSize.w - textRect.w) / 2;
            textRect.y = (windowSize.h - textRect.h) / 2;

            SDL_RenderCopy(renderer, texture, nullptr, &textRect);
            SDL_DestroyTexture(texture);
        }

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:
                case SDL_KEYDOWN:
                    running = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT){
                        int i = event.button.y / rect.h * elementPerLine + event.button.x / rect.w;
                        if (i < apps.size()){
                            currentApp = &apps[i];
                            std::cout << "Starting " << currentApp->name << std::endl;
                            currentPid = startWineApp(*currentApp);
                        } else {
                            std::cout << "Click is out of bounds." << std::endl;
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        usleep(16000);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}