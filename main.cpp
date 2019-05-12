#include "model.h"
#include "game.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QTime>


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

    menu me;
    MainWindow ma;
    Model mo;

    Controller controller(&me,&ma,&mo);
    controller.startGame();

    return a.exec();
}



