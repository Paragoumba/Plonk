#include "App.hpp"
#include "ui_App.h"

App::App(QWidget* parent) :
        QWidget(parent), ui(new Ui::App){
    ui->setupUi(this);
}

App::App(const std::string& s): App(){
    ui->appName->setText(QString::fromStdString(s));
}

App::~App(){
    delete ui;
}