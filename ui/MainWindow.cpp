#include <QLabel>
#include "MainWindow.hpp"
#include "ui_MainWindow.hpp"
#include "App.hpp"

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    ui->gridLayout->addWidget(new App("Test"), 2, 2);
}

MainWindow::~MainWindow(){
    delete ui;
}
