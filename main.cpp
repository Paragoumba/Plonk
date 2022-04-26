#include <iostream>
#include <unistd.h>
#include <vector>
#include <pwd.h>

#include <QApplication>
#include <QGridLayout>

#include "ui/MainWindow.hpp"

struct AppInfo {
    std::string name;
    std::string path;
    std::string wineprefix = std::string(getpwuid(getuid())->pw_dir) + "/.wine";
};

pid_t startWineApp(const AppInfo& app){
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

int main(int argc, char** argv){
    std::vector<AppInfo> apps = {
            {"Wine Test", "../test/win.exe"},
            /*{"New AppInfo", "/path/to/executable", "/path/to/custom/wineprefix"}*/};

    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return QApplication::exec();
}