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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->mapScene = new QGraphicsScene();
    this->cameraView = new Scene(); // "la camera mobile"

    currentMap.push_back("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    currentMap.push_back("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    currentMap.push_back("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    currentMap.push_back("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    currentMap.push_back("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    currentMap.push_back("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    currentMap.push_back("00000000000;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;00000000000000000000000");
    currentMap.push_back("00000000000;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;0000000000000000000");
    currentMap.push_back("00000000000.....................................................................................................00000000000");
    currentMap.push_back("00000000000.......................OOOOOOOO..................................../////////////////.................00000000000");
    currentMap.push_back("00000000000..///////////..........OOOOOOOO..................................../M/M/M/M/M/M/M/M/.................00000000000");
    currentMap.push_back("00000000000..///M/M/M/M/..........OOOOOOOO.....................................//M/M//M/M/////..................00000000000");
    currentMap.push_back("00000000000../M/M/M/..............OOOOOOOO....................................../////////.......................00000000000");
    currentMap.push_back("00000000000..//M/M/.............................................................................................00000000000");
    currentMap.push_back("00000000000.../M/M/M/M/M/M/.....................................................................................00000000000");
    currentMap.push_back("00000000000.....................................................................................................00000000000");
    currentMap.push_back("00000000000...............................................................//////////////////////////////////////00000000000");
    currentMap.push_back("00000000000...............................................................//////////////////////////////////////00000000000");
    currentMap.push_back("00000000000...............................................................//////////////////////////////////////00000000000");
    currentMap.push_back("00000000000...............................................................//////////////////////////////////////00000000000");
    currentMap.push_back("00000000000......../////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000......................./////////////////////////////////////...........................//////////////00000000000");
    currentMap.push_back("00000000000.....................................................................................................00000000000");
    currentMap.push_back("00000000000.....................................TTTT............................................................00000000000");
    currentMap.push_back("00000000000.....................................TTTT............................................................00000000000");
    currentMap.push_back("00000000000.....................................TTTTTTTTTTTTTTTTTTTTT...........................................00000000000");
    currentMap.push_back("00000000000.....................................TTTTTTTTTTTTTTTTTTTTT...........................................00000000000");
    currentMap.push_back("00000000000.....................................TTTTTTTTTTTTTTTTTTTTT...........................................00000000000");
    currentMap.push_back("00000000000.....................................TTTTTTTTTTTTTTTTTTTTT........TTTTTTTTTTTTTTTTTTTTT..............00000000000");
    currentMap.push_back("00000000000..................................................................TTTTTTTTTTTTTTTTTTTTT..............00000000000");
    currentMap.push_back("00000000000..................................................................TTTTTTTTTTTTTTTTTTTTT..............00000000000");
    currentMap.push_back("00000000000..................................................................TTTTTTTTTTTTTTTTTTTTT..............00000000000");
    currentMap.push_back("00000000000..................................................................TTTT...............................00000000000");
    currentMap.push_back("00000000000..................................................................TTTT......///////////..............00000000000");
    currentMap.push_back("00000000000....................................TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT....../M/M///M/M/..............00000000000");
    currentMap.push_back("00000000000....................................TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT......///////////..............00000000000");
    currentMap.push_back("00000000000....................................TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT...............................00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("00000000000/////////////////////////////////////////////////////////////////////////////////////////////////////00000000000");
    currentMap.push_back("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    currentMap.push_back("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    currentMap.push_back("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    currentMap.push_back("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    currentMap.push_back("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    currentMap.push_back("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    currentMap.push_back("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

    /*  Fit the cellTypes map with the type of all cells in the map */
    cellTypes["."] = 1; /* Sand (can walk on it) */
    cellTypes[";"] = 1; /* Grass (can walk on it) */
    cellTypes["/"] = 1; /* dirt (can walk on it) */
    cellTypes["0"] = 0; /* Wall (can't walk on it) */
    cellTypes["O"] = 0; /* Water (can't walk on it) */
    cellTypes["T"] = 0; /* Tree (can't walk on it) */
    cellTypes["M"] = 0; /* House (can't walk on it) */

    this->ennemisList.push_back(new Ennemis(13 * 50 , 17 * 50));
    this->ennemisList.push_back(new Ennemis(14 * 50 , 16 * 50));
    this->ennemisList.push_back(new Ennemis(16 * 50 , 12 * 50));
    this->ennemisList.push_back(new Ennemis(18 * 50 , 10 * 50));
    this->ennemisList.push_back(new Ennemis(19 * 50 , 9 * 50));
    this->ennemisList.push_back(new Ennemis(26 * 50 , 14 * 50));
    this->ennemisList.push_back(new Ennemis(27 * 50 , 8 * 50));
    this->ennemisList.push_back(new Ennemis(27 * 50 , 20 * 50));

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

            if (currentMap[i][j] == ";"){
                QGraphicsPixmapItem *grass = new QGraphicsPixmapItem();

                int randomNumer = rand()%13;
                QPixmap tile = QPixmap("");
                if(randomNumer==1)
                    tile = QPixmap(":/terrain/Images/Terrain/grass_1.png");
                else if(randomNumer==2)
                    tile = QPixmap(":/terrain/Images/Terrain/grass_2.png");
                else if(randomNumer==3)
                    tile = QPixmap(":/terrain/Images/Terrain/grass_3.png");
                else if(randomNumer==4)
                    tile = QPixmap(":/terrain/Images/Terrain/grass_4.png");
                else if(randomNumer==5)
                    tile = QPixmap(":/terrain/Images/Terrain/grass_5.png");
                else if(randomNumer==6)
                    tile = QPixmap(":/terrain/Images/Terrain/grass_6.png");
                else if(randomNumer==7)
                    tile = QPixmap(":/terrain/Images/Terrain/grass_7.png");
                else if(randomNumer==8)
                    tile = QPixmap(":/terrain/Images/Terrain/grass_8.png");
                else if(randomNumer==9)
                    tile = QPixmap(":/terrain/Images/Terrain/grass_9.png");
                else if(randomNumer==10)
                    tile = QPixmap(":/terrain/Images/Terrain/grass_10.png");
                else if(randomNumer==11)
                    tile = QPixmap(":/terrain/Images/Terrain/grass_11.png");
                else if(randomNumer==12)
                    tile = QPixmap(":/terrain/Images/Terrain/grass_12.png");

                grass->setPixmap(QPixmap(":/terrain/Images/Terrain/grass_12.png"));

                grass->setPos(j*50,i*50);
                this->mapScene -> addItem(grass);
            }
            else if (currentMap[i][j] == "0"){
                QGraphicsPixmapItem *wall = new QGraphicsPixmapItem();
                wall->setPixmap(QPixmap(":/terrain/Images/Terrain/wall.jpg"));
                wall->setPos(j*50,i*50);
                this->mapScene -> addItem(wall);
            }
            else if (currentMap[i][j] == "O"){
                QGraphicsPixmapItem *water = new QGraphicsPixmapItem();
                int i = rand()%13;
                water->setPixmap(QPixmap(":/terrain/Images/Terrain/water_" + QString(i) + ".png"));
                water->setPos(j*50,i*50);
                this->mapScene -> addItem(water);
            }
            else if (currentMap[i][j] == "."){
                QGraphicsPixmapItem *sand = new QGraphicsPixmapItem();
                sand->setPixmap(QPixmap(":/terrain/Images/Terrain/Sand.jpg"));
                sand->setPos(j*50,i*50);
                this->mapScene -> addItem(sand);
            }
            else if (currentMap[i][j] == "/"){
                QGraphicsPixmapItem *dirt = new QGraphicsPixmapItem();
                dirt->setPixmap(QPixmap(":/terrain/Images/Terrain/dirt.jpg"));
                dirt->setPos(j*50,i*50);
                this->mapScene -> addItem(dirt);
            }
            else if (currentMap[i][j] == "T"){
                QGraphicsPixmapItem *tree = new QGraphicsPixmapItem();
                tree->setPixmap(QPixmap(":/terrain/Images/Terrain/tree.jpg"));
                tree->setPos(j*50,i*50);
                this->mapScene -> addItem(tree);
            }
            else if (currentMap[i][j] == "M"){
                QGraphicsPixmapItem *house = new QGraphicsPixmapItem();
                house->setPixmap(QPixmap(":/terrain/Images/Terrain/house.jpg"));
                house->setPos(j*50,i*50);
                this->mapScene -> addItem(house);
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

void MainWindow::displayZelda(Zelda *zelda)
{
    QGraphicsPixmapItem *tileZelda =  new QGraphicsPixmapItem(zelda->getTile());
    tileZelda->setPos(zelda->getPosX(),zelda->getPosY());
    this->mapScene->addItem(tileZelda);
}

void MainWindow::displayEnnemis(Ennemis *ennemi)
{
    QGraphicsPixmapItem *tileEnnemi =  new QGraphicsPixmapItem(ennemi->getTile());
    tileEnnemi->setPos(ennemi->getPosX(),ennemi->getPosY());
    this->mapScene->addItem(tileEnnemi);
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

std::vector<QString> MainWindow::getCurrentMap()
{
    return currentMap;
}

std::map<QString, int> MainWindow::getCellTypes()
{
    return cellTypes;
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

