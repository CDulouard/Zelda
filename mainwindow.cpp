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
    this->cameraView = new Scene();

    currentMap.push_back("..........................................");
    currentMap.push_back("..........................................");
    currentMap.push_back("..........................................");
    currentMap.push_back("..........................................");
    currentMap.push_back("..........................................");
    currentMap.push_back("..........................................");
    currentMap.push_back("..........................................");
    currentMap.push_back("...........gggggggggggggggggggg...........");
    currentMap.push_back("...........ggggggggggwwwwwwwwww...........");
    currentMap.push_back("...........gggggggggwwwwwwwwwww...........");
    currentMap.push_back("...........gggggggggwwwwwwwwwww...........");
    currentMap.push_back("...........ggggggggggwwwwwwwwww...........");
    currentMap.push_back("...........gggggggggggggwwwwwww...........");
    currentMap.push_back("...........gggggggggggggssggggg...........");
    currentMap.push_back("...........gggggggggggggwwggggg...........");
    currentMap.push_back("...........ggggggggggggwwgggggg...........");
    currentMap.push_back("...........gggggggggggwwwgggggg...........");
    currentMap.push_back("...........tttttttggggwwwgggggg...........");
    currentMap.push_back("...........dhddddtggggwwwgggggg...........");
    currentMap.push_back("...........hdddddtgggwwwggggggg...........");
    currentMap.push_back("...........hdddddgggwwwgggggggg...........");
    currentMap.push_back("..........................................");
    currentMap.push_back("..........................................");
    currentMap.push_back("..........................................");
    currentMap.push_back("..........................................");
    currentMap.push_back("..........................................");
    currentMap.push_back("..........................................");
    currentMap.push_back("..........................................");


    /*  Fit the cellTypes map with the type of all cells in the map */
    cellTypes["g"] = 1; /* Grass (can walk on it) */
    cellTypes["s"] = 1; /* Sand (can walk on it) */
    cellTypes["d"] = 1; /* dirt (can walk on it) */
    cellTypes["."] = 0; /* Wall (can't walk on it) */
    cellTypes["w"] = 0; /* Water (can't walk on it) */
    cellTypes["t"] = 0; /* Tree (can't walk on it) */
    cellTypes["h"] = 0; /* House (can't walk on it) */

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

            if (currentMap[i][j] == "g"){
                QGraphicsPixmapItem *grass = new QGraphicsPixmapItem();
                grass->setPixmap(QPixmap(":/terrain/Images/Terrain/grass_12.png"));
                grass->setPos(j*50,i*50);
                this->mapScene -> addItem(grass);
            }
            else if (currentMap[i][j] == "."){
                QGraphicsPixmapItem *wall = new QGraphicsPixmapItem();
                wall->setPixmap(QPixmap(":/terrain/Images/Terrain/wall.jpg"));
                wall->setPos(j*50,i*50);
                this->mapScene -> addItem(wall);
            }
            else if (currentMap[i][j] == "w"){
                QGraphicsPixmapItem *water = new QGraphicsPixmapItem();
                water->setPixmap(QPixmap(":/terrain/Images/Terrain/water_1.png"));
                water->setPos(j*50,i*50);
                this->mapScene -> addItem(water);
            }
            else if (currentMap[i][j] == "s"){
                QGraphicsPixmapItem *sand = new QGraphicsPixmapItem();
                sand->setPixmap(QPixmap(":/terrain/Images/Terrain/Sand.jpg"));
                sand->setPos(j*50,i*50);
                this->mapScene -> addItem(sand);
            }
            else if (currentMap[i][j] == "d"){
                QGraphicsPixmapItem *dirt = new QGraphicsPixmapItem();
                dirt->setPixmap(QPixmap(":/terrain/Images/Terrain/dirt.jpg"));
                dirt->setPos(j*50,i*50);
                this->mapScene -> addItem(dirt);
            }
            else if (currentMap[i][j] == "t"){
                QGraphicsPixmapItem *tree = new QGraphicsPixmapItem();
                tree->setPixmap(QPixmap(":/terrain/Images/Terrain/tree.png"));
                tree->setPos(j*50,i*50);
                this->mapScene -> addItem(tree);
            }
            else if (currentMap[i][j] == "h"){
                QGraphicsPixmapItem *water = new QGraphicsPixmapItem();
                water->setPixmap(QPixmap(":/terrain/Images/Terrain/house.jpg"));
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

void MainWindow::deleteItem(int nbItem)
{
    if(this->mapItems.size()!=0){
        delete this->mapItems[nbItem];
        this->mapItems.erase(this->mapItems.begin()+nbItem);
    }
}

void MainWindow::deleteMonster(int nbMonster)
{
    delete this->ennemisList[nbMonster];
    this->ennemisList.erase(this->ennemisList.begin()+nbMonster);

}

void MainWindow::displayMapItems(std::vector<Item *> vec)
{
    if(vec.size()!=0){
        for (unsigned long i = 0; i<vec.size(); i++){
            QPixmap pix = vec[i]->getTile();
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pix);
            item->setPos(vec[i]->getPosXactuel(),vec[i]->getPosYactuel());
            item->setZValue(10);
            this->mapScene->addItem(item);
        }
    }
}

std::vector<Item *> MainWindow::getMapItems() const
{
    return this->mapItems;
}
