/********************************************************************************
** Form generated from reading UI file 'App.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APP_H
#define UI_APP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_App
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *appIcon;
    QLabel *appName;

    void setupUi(QWidget *App)
    {
        if (App->objectName().isEmpty())
            App->setObjectName(QString::fromUtf8("App"));
        App->resize(400, 300);
        widget = new QWidget(App);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(170, 80, 60, 41));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        appIcon = new QLabel(widget);
        appIcon->setObjectName(QString::fromUtf8("appIcon"));
        appIcon->setScaledContents(true);

        verticalLayout->addWidget(appIcon);

        appName = new QLabel(widget);
        appName->setObjectName(QString::fromUtf8("appName"));
        appName->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(appName);


        retranslateUi(App);

        QMetaObject::connectSlotsByName(App);
    } // setupUi

    void retranslateUi(QWidget *App)
    {
        App->setWindowTitle(QCoreApplication::translate("App", "App", nullptr));
        appIcon->setText(QCoreApplication::translate("App", "<html><head/><body><img></img></body></html>", nullptr));
        appName->setText(QCoreApplication::translate("App", "App name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class App: public Ui_App {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP_H
