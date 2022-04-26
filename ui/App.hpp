#ifndef PLONK_APP_HPP
#define PLONK_APP_HPP

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class App; }
QT_END_NAMESPACE

class App : public QWidget {
Q_OBJECT

public:
    explicit App(QWidget* parent = nullptr);
    explicit App(const std::string& s);

    ~App() override;

private:
    Ui::App* ui;
};

#endif //PLONK_APP_HPP
