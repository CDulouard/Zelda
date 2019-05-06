#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "Debug.h"
#include <QString>

#include "menu.h"
#include <QSplashScreen>


#include <iostream>
#include <vector>
#include <chrono>
#include <map>


#include "Debug.h"
#include "Map.h"

#include <QDebug>

using namespace std;


/*  Globals variables    */

static bool keepPlaying = true;
vector<QString> currentMap;
map<QString, int> cellTypes;

static double DELTATIME;

void Start() {
    /*  Executed once   */
    DELTATIME = 0;
    //currentMap = ReadMap(":/map/save/world.txt");

    /*  Fit the cellTypes map with the type of all cells in the map */

    cellTypes["0"] = 0; /*  Ground (can walk on it) */
    cellTypes["x"] = 1; /*  Wall (can't walk on it) */

    currentMap.push_back("xxxxxxxxxxxxxxxxxxxx");
    currentMap.push_back("x000000000000000000x");
    currentMap.push_back("x000000000000000000x");
    currentMap.push_back("x000000000000000000x");
    currentMap.push_back("x000000000000000000x");
    currentMap.push_back("x000000000000000000x");
    currentMap.push_back("x000000000000000000x");
    currentMap.push_back("x000000000000000000x");
    currentMap.push_back("x000000000000000000x");
    currentMap.push_back("x000000000000000000x");
    currentMap.push_back("x000000000000000000x");
    currentMap.push_back("x000000000000000000x");
    currentMap.push_back("xxxxxxxxxxxxxxxxxxxx");

}

int main(int argc, char *argv[])
{
    Start();
    QApplication a(argc, argv);

    //Add Splash Screen
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/Menu/Images/SplashScreen.png"));
    splash->show();


    menu menu;
    menu.show();


    return a.exec();
}
