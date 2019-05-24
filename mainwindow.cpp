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

    mapGenerator();

}

void MainWindow::mapGenerator()
{
    // first case of the map (not the rim) is (11,7)

    currentMap.push_back("......................................................................");
    currentMap.push_back("......................................................................");
    currentMap.push_back("......................................................................");
    currentMap.push_back("......................................................................");
    currentMap.push_back("......................................................................");
    currentMap.push_back("......................................................................");
    currentMap.push_back("..........rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr..........");
    currentMap.push_back("..........rggggggtttttttgggggttggggtttgggswwwwwsggggtttttttr..........");
    currentMap.push_back("..........rtgggggtttggtgggggggggggggtgggswwwwwsggggggttttttr..........");
    currentMap.push_back("..........rtgggggggtgggggggtgggggggggggswwwwwsggggggtttttttr..........");
    currentMap.push_back("..........rggggggggggggtggggggggggggggggswwwwwsgggggggtttttr..........");
    currentMap.push_back("..........rgggggggggdddddgggggggtgggggggswwwwwsggggggggggttr..........");
    currentMap.push_back("..........rgggggggdddhddhddgggtggggggggswwwwwsgggggggggggggr..........");
    currentMap.push_back("..........rgggggddddddhddddhdggggggggtsswwwwwsggddttgggggggr..........");
    currentMap.push_back("..........rttgggggddddddddhgggggtgggggsswwwwssgddhdddggggtgr..........");
    currentMap.push_back("..........rtggggggddhddddtgggggggggggssswwwssshddddddddggggr..........");
    currentMap.push_back("..........rgggggggggddddggggggggggggggsswwwssddddddhddgggggr..........");
    currentMap.push_back("..........rttggggggggggggggtttgggggggggswwwsgddhdddddggggggr..........");
    currentMap.push_back("..........rttttggggggggggtttttttttggggg12223ggdddhddgggggggr..........");
    currentMap.push_back("..........rtttttttggggggtttttttttttttggswwwssgggdddggggttggr..........");
    currentMap.push_back("..........rggttttttttggtttttttttttttttswwwwwssgggggggtttttgr..........");
    currentMap.push_back("..........rggggttttggggtttttttttttttttwwwwwwwwssggggtttttttr..........");
    currentMap.push_back("..........rgggttttggtggggttttttttttggswwwwwwwwwssggggttttttr..........");
    currentMap.push_back("..........rtgggttgggttggttggttttttggsswwwwwwwwwsssggggggtttr..........");
    currentMap.push_back("..........rttggtggggtggggggggttgggsswwwwwwwwwwwwssgtgggggttr..........");
    currentMap.push_back("..........rtggggggtggggtttgggggggsswwwwwwwwwwwwwwwssggggggtr..........");
    currentMap.push_back("..........rggggggtttggggtgggggggswwwwwwwwwwwwwwwwsssgggggggr..........");
    currentMap.push_back("..........rggggggtgtgggggggggggswwwwwwwwwwwwwwwwwwsgggggtggr..........");
    currentMap.push_back("..........rggggggggggggggggggggswwwwwwwwwwwwwwwwwssggggggggr..........");
    currentMap.push_back("..........rssggggggggggggggggggswwwwwwwwwwwwwwwwwwsggtgggggr..........");
    currentMap.push_back("..........rwwsgggggggggggggggggsswwwwwwwwwwwwwwwwssggggggggr..........");
    currentMap.push_back("..........rwwwsssggddgggggggggggsswwwwwwwwwwwwwwssggttgggtgr..........");
    currentMap.push_back("..........rwwwwwwshddhdggggggggggssswwwwwwwwwwwwssgggtgggggr..........");
    currentMap.push_back("..........rwwwwwssdddddggggtggggggswwwwwwwwwwwwsssgggggggggr..........");
    currentMap.push_back("..........rwwwwssddhddggggggggggtswwwwwwwwwwwwsggggggtgggggr..........");
    currentMap.push_back("..........rwwwssggddhgggtgggggggswwwwwwwwwwwsssgggtggggggggr..........");
    currentMap.push_back("..........rwwssggggddgggggggggggswwwwwwwwwwssggggggggggggggr..........");
    currentMap.push_back("..........rsssggggggggggttgggggggswwwwwwwwssgggggggttggggggr..........");
    currentMap.push_back("..........rgggggggggggggtggggggggswwwwwwwssgggggggddhdgggggr..........");
    currentMap.push_back("..........rgggggggggggggggggggggggswwwwwssgggggggdhddddtgggr..........");
    currentMap.push_back("..........rggggggggggggggggggggggggswwwssgggggggggdddtttgggr..........");
    currentMap.push_back("..........rggggggggttttgggggggggggggswwssggggggggggggttttttr..........");
    currentMap.push_back("..........rggggggggggtttggggggggggggswwsgggggggggggtttttgggr..........");
    currentMap.push_back("..........rttgggggggtttggggggggggggswwsggggggggggttttttttttr..........");
    currentMap.push_back("..........rtgggggggtttggggggggggggswwsgggggggggttttttttttttr..........");
    currentMap.push_back("..........rtttgggtttttttggggggggggswwsgggggttttttttttttttttr..........");
    currentMap.push_back("..........rtttttttttttttttddhdtttttswwsgtttttttttttttttttttr..........");
    currentMap.push_back("..........rttttttttttttttttddtttttwwwttttttttttttttttttttttr..........");
    currentMap.push_back("..........rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr..........");
    currentMap.push_back("......................................................................");
    currentMap.push_back("......................................................................");
    currentMap.push_back("......................................................................");
    currentMap.push_back("......................................................................");
    currentMap.push_back("......................................................................");
    currentMap.push_back("......................................................................");


    /*  Fit the cellTypes map with the type of all cells in the map */
    cellTypes["g"] = 1; /* Grass (can walk on it) */
    cellTypes["s"] = 1; /* Sand (can walk on it) */
    cellTypes["d"] = 1; /* dirt (can walk on it) */
    cellTypes["1"] = 1; /* bridge (can walk on it) */
    cellTypes["2"] = 1; /* bridge (can walk on it) */
    cellTypes["3"] = 1; /* bridge (can walk on it) */
    cellTypes["."] = 0; /* void (can't walk on it) */
    cellTypes["r"] = 0; /* rims (can't walk on it) */
    cellTypes["w"] = 0; /* Water (can't walk on it) */
    cellTypes["t"] = 0; /* Tree (can't walk on it) */
    cellTypes["h"] = 0; /* House (can't walk on it) */

    if(this->getMapItems().size() > 0){
        for (unsigned int i = 0 ; i < this->getMapItems().size() ; i++ ){
            this->deleteItem(int(i));
            qDebug() << "ça narche1";
        }
    }

    if(this->getEnnemisList().size() > 0){
        for (unsigned int i = 0 ; i < this->getEnnemisList().size() ; i++ ){
            this->deleteMonster(int(i));
            qDebug() << "ça marche2";
        }
    }


//    this->ennemisList.push_back(new Ennemis(12 * 50 , 53 * 50));
//    this->ennemisList.push_back(new Ennemis(14 * 50 , 43 * 50));
//    this->ennemisList.push_back(new Ennemis(17 * 50 , 47 * 50));
//    this->ennemisList.push_back(new Ennemis(26 * 50 , 57 * 50));
//    this->ennemisList.push_back(new Ennemis(25 * 50 , 46 * 50));
//    this->ennemisList.push_back(new Ennemis(27 * 50 , 41 * 50));
//    this->ennemisList.push_back(new Ennemis(35 * 50 , 53 * 50));
//    this->ennemisList.push_back(new Ennemis(38 * 50 , 57 * 50));
//    this->ennemisList.push_back(new Ennemis(44 * 50 , 42 * 50));
//    this->ennemisList.push_back(new Ennemis(46 * 50 , 55 * 50));
//    this->ennemisList.push_back(new Ennemis(12 * 50 , 19 * 50));

//    this->ennemisList.push_back(new Ennemis(18 * 50 , 77 * 50));
//    this->ennemisList.push_back(new Ennemis(13 * 50 , 79 * 50));
//    this->ennemisList.push_back(new Ennemis(19 * 50 , 85 * 50));
//    this->ennemisList.push_back(new Ennemis(31 * 50 , 83 * 50));
//    this->ennemisList.push_back(new Ennemis(40 * 50 , 85 * 50));
//    this->ennemisList.push_back(new Ennemis(44 * 50 , 71 * 50));


    this->ennemisList.push_back(new Ennemis(15 * 50 , 15 * 50));
    this->ennemisList.push_back(new Ennemis(20 * 50 , 20 * 50));

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
                grass->setPixmap(QPixmap(":/terrain/Images/Terrain/grass_10.png"));
                grass->setPos(j*50,i*50);
                this->mapScene -> addItem(grass);
            }
            else if (currentMap[i][j] == "."){
                QGraphicsPixmapItem *fogOfWar = new QGraphicsPixmapItem();
                fogOfWar->setPixmap(QPixmap(":/terrain/Images/Terrain/void.png"));
                fogOfWar->setPos(j*50,i*50);
                this->mapScene -> addItem(fogOfWar);
            }
            else if (currentMap[i][j] == "r"){
                QGraphicsPixmapItem *fogOfWar = new QGraphicsPixmapItem();
                fogOfWar->setPixmap(QPixmap(":/terrain/Images/Terrain/wall.jpg"));
                fogOfWar->setPos(j*50,i*50);
                this->mapScene -> addItem(fogOfWar);
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

            else if (currentMap[i][j] == "1"){
                QGraphicsPixmapItem *bridge1 = new QGraphicsPixmapItem();
                bridge1->setPixmap(QPixmap(":/terrain/Images/Terrain/bridge_left.jpg"));
                bridge1->setPos(j*50,i*50);
                this->mapScene -> addItem(bridge1);
            }

            else if (currentMap[i][j] == "2"){
                QGraphicsPixmapItem *bridge2 = new QGraphicsPixmapItem();
                bridge2->setPixmap(QPixmap(":/terrain/Images/Terrain/bridge.png"));
                bridge2->setPos(j*50,i*50);
                this->mapScene -> addItem(bridge2);
            }

            else if (currentMap[i][j] == "3"){
                QGraphicsPixmapItem *bridge3 = new QGraphicsPixmapItem();
                bridge3->setPixmap(QPixmap(":/terrain/Images/Terrain/bridge_right.jpg"));
                bridge3->setPos(j*50,i*50);
                this->mapScene -> addItem(bridge3);
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
    case Qt::Key_K:
    {
        if(event->isAutoRepeat())
            break;
        else {
            pointeurControlleur->pressKey("k");
            break;
        }
    }
    case Qt::Key_L:
    {
        if(event->isAutoRepeat())
            break;
        else {
            pointeurControlleur->pressKey("l");
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


