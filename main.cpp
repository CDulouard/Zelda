#include "ui_mainwindow.h"
#include "mainwindow.h"

#include "menu.h"
#include <QSplashScreen>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Add Splash Screen
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/Menu/Images/SplashScreen.png"));
    splash->show();


    menu menu;
    menu.show();

    return a.exec();
}
