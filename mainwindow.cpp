#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"
#include "ennemis.h"
#include "zelda.h"
#include "item.h"

#include <vector>
#include <QKeyEvent>

using namespace std;

extern Controller *pointeurControlleur;
static bool keepPlaying = true;
static double DELTATIME;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->mapScene = new QGraphicsScene();
    this->cameraView = new Scene(); // "la camera mobile"

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

    this->ennemisList.push_back(new Ennemis(150,150));
    this->ennemisList.push_back(new Ennemis(400,250));
    this->ennemisList.push_back(new Ennemis(250,400));
    this->ennemisList.push_back(new Ennemis(500,400));
    this->ennemisList.push_back(new Ennemis(400,400));
    this->ennemisList.push_back(new Ennemis(300,430));
    this->ennemisList.push_back(new Ennemis(250,460));
    this->ennemisList.push_back(new Ennemis(800,250));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetView(){
    delete this->mapScene;
    this->mapScene = new QGraphicsScene();
}

void MainWindow::displayMap()
{
    mapScene->setSceneRect(this->cameraView->getPosX(),this->cameraView->getPosY(),500,500); // on définie la camera

    for (unsigned int i = 0 ; i < currentMap.size() ; i++) {
        for (int j = 0 ; j < currentMap[0].size() ; j++){

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
    QGraphicsPixmapItem *tileLink =  new QGraphicsPixmapItem(link->getTile());
    tileLink->setPos(link->getPosX(),link->getPosY());
    this->mapScene->addItem(tileLink);
}

void MainWindow::displayEnnemis(Ennemis *ennemi)
{
    QGraphicsPixmapItem *tileEnnemi =  new QGraphicsPixmapItem(ennemi->getTile());
    tileEnnemi->setPos(ennemi->getPosX(),ennemi->getPosY());
    this->mapScene->addItem(tileEnnemi);
}

void MainWindow::displayZelda(Zelda *Zelda)
{
    Zelda->setPosX(this->currentMap[0].size()*50 - 100);
    Zelda->setPosY(this->currentMap.size() * 50 - 100);
    QGraphicsPixmapItem *tileZelda =  new QGraphicsPixmapItem(Zelda->getTile());
    tileZelda->setPos(Zelda->getPosX(),Zelda->getPosY());
    this->mapScene->addItem(tileZelda);
}

void MainWindow::displayStats(int health, int arrowNmber, int energy)
{
    this->ui->Health_display->display(health);
    this->ui->Arrows_display->display(arrowNmber);
    this->ui->Energy_display->display(energy);
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

QGraphicsScene *MainWindow::getMapScene() const
{
    return mapScene;
}

Scene *MainWindow::getCameraView() const
{
    return cameraView;
}

void MainWindow::setCameraView(Scene *value)
{
    cameraView = value;
}

vector<Ennemis *> MainWindow::getEnnemisList() const
{
    return ennemisList;
}

void MainWindow::setEnnemisList(const vector<Ennemis*> &value)
{
    ennemisList = value;
}

void MainWindow::ajouterItem(int posX, int posY, QString s)
{
    this->mapItems.push_back(new Item(posX, posY, s));
}

