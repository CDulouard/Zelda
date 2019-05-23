#include "model.h"
#include "mainwindow.h"
#include "menu.h"
#include "controller.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QDebug>

Controller *pointeurControlleur;


void delay(int i) //wait i ms
{
    QTime dieTime= QTime::currentTime().addMSecs(i);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Add Splash Screen
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/Menu/Images/SplashScreen.png"));
    splash->show();
    delay(2000);
    splash->close();

    Model mo;
    menu me;
    MainWindow ma;

    Controller controller(&me,&ma,&mo);
    pointeurControlleur = &controller;
    controller.startGame();

    return a.exec();
}
