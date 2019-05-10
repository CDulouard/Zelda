#include "model.h"
#include "map.h"
#include "controller.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>


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

    Map ma;
    Model mo;

    Controller controller(&ma,&mo);
    controller.startApplication();

    return a.exec();
}



