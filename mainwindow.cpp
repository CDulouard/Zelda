#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>

/*  Globals variables    */
static bool keepPlaying = true;
static double DELTATIME;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->mapScene = new QGraphicsScene();
    this->cameraView = new Scene(); // "la camera mobile"
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetView(){
    delete this->mapScene;
    delete this->cameraView;
    this->mapScene = new QGraphicsScene(); // fixe
    this->cameraView = new Scene(); // "la camera mobile"
}

void MainWindow::displayMap()
{

    /*  Executed once   */
    DELTATIME = 0;
    //currentMap = ReadMap(":/map/save/world.txt");

    /*  Fit the cellTypes map with the type of all cells in the map */

    cellTypes["0"] = 1; /*  Ground (can walk on it) */
    cellTypes["x"] = 0; /*  Wall (can't walk on it) */
    cellTypes["w"] = 0; /*  Water (can't walk on it) */

    currentMap.push_back("xxxxxxxxxxxxxxxxxxxx");
    currentMap.push_back("x000000000000000w00x");
    currentMap.push_back("x000000000000000w00x");
    currentMap.push_back("x000000000000000w00x");
    currentMap.push_back("x000000000000000w00x");
    currentMap.push_back("x000000000000000wwwx");
    currentMap.push_back("x000000000000000000x");
    currentMap.push_back("x000000000000000000x");
    currentMap.push_back("x000000000000000000x");
    currentMap.push_back("x000000000000000000x");
    currentMap.push_back("xww0000000000000000x");
    currentMap.push_back("xww0000000000000000x");
    currentMap.push_back("xxxxxxxxxxxxxxxxxxxx");

    mapScene->setSceneRect(this->cameraView->getPosX(),this->cameraView->getPosY(),500,500); // on définie la camera

    for (unsigned int i = 0 ; i < currentMap.size() ; i++) {
        for (unsigned int j = 0 ; j < 20 ; j++){

            if (currentMap[i][j] == "0"){
                QGraphicsPixmapItem *grass = new QGraphicsPixmapItem();
                grass->setPixmap(QPixmap(":/terrain/Images/Terrain/Grass.jpg"));
                grass->setPos(j*50,i*50);
                this->mapScene -> addItem(grass);
            }
            else if (currentMap[i][j] == "x"){
                QGraphicsPixmapItem *wall = new QGraphicsPixmapItem();
                wall->setPixmap(QPixmap(":/terrain/Images/Terrain/wall.jpg"));
                wall->setPos(j*50,i*50);
                this->mapScene -> addItem(wall);
            }
            else if (currentMap[i][j] == "w"){
                QGraphicsPixmapItem *water = new QGraphicsPixmapItem();
                water->setPixmap(QPixmap(":/terrain/Images/Terrain/Water.jpg"));
                water->setPos(j*50,i*50);
                this->mapScene -> addItem(water);
            }
        }
    }

    ui->graphicsView->setScene(this->mapScene);
}

void MainWindow::displayLink(Link *link)
{
    QGraphicsPixmapItem *apparencePersonnage =  new QGraphicsPixmapItem(link->getTile());
    apparencePersonnage->setPos(link->getPosX(),link->getPosY());
    //apparencePersonnage->setZValue(100);//pour etre sur
    this->mapScene->addItem(apparencePersonnage);
}


