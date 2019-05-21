#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "controller.h"

#include <vector>
#include <QKeyEvent>

extern Controller *pointeurControlleur;
static bool keepPlaying = true;
static double DELTATIME;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->mapScene = new QGraphicsScene();
    this->cameraView = new Scene(); // "la camera mobile"
    this->cameraView->setPosX(0);
    this->cameraView->setPosY(0);

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
    this->mapScene->addItem(apparencePersonnage);
}


void MainWindow::keyPressEvent(QKeyEvent *event)// je gére quand j'appuie sur une touche
{
    switch ( event->key())
    {
    case Qt::Key_Enter:
    {
        pointeurControlleur->pressKey("enter");
        break;
    }
    case Qt::Key_Escape:
    {
        pointeurControlleur->pressKey("escape");
        break;
    }
    case Qt::Key_Right:
    {
        pointeurControlleur->pressKey("right");
        break;
    }
    case Qt::Key_D:
    {
        pointeurControlleur->pressKey("right");
        break;
    }
    case Qt::Key_Left:
    {
        pointeurControlleur->pressKey("left");
        break;
    }
    case Qt::Key_A:
    {
        pointeurControlleur->pressKey("left");
        break;
    }
    case Qt::Key_Down:
    {
        pointeurControlleur->pressKey("down");
        break;
    }
    case Qt::Key_S:
    {
        pointeurControlleur->pressKey("down");
        break;
    }
    case Qt::Key_Up:
    {
        pointeurControlleur->pressKey("up");
        break;
    }
    case Qt::Key_W:
    {
        pointeurControlleur->pressKey("up");
        break;
    }
    case Qt::Key_H:
    {
        if(event->isAutoRepeat())
            break;
        else {
            pointeurControlleur->pressKey("h");
            break;
        }
    }
    case Qt::Key_J:
    {
        if(event->isAutoRepeat())
            break;
        else {
            pointeurControlleur->pressKey("j");
            break;
        }
    }
    case Qt::Key_K:
    {
        if(event->isAutoRepeat())
            break;
        else {
            pointeurControlleur->pressKey("k");
            break;
        }
    }
    }
}

Scene *MainWindow::getCameraView() const
{
    return cameraView;
}

void MainWindow::setCameraView(Scene *value)
{
    cameraView = value;
}


