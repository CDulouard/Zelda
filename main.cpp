#include "model.h"
#include "map.h"
#include "controller.h"

#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Add Splash Screen
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/Menu/Images/SplashScreen.png"));
    splash->show();

    Map ma;
    Model mo;

    Controller controller(&ma,&mo);
    controller.startApplication();

    return a.exec();
}



