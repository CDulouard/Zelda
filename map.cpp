#include "map.h"

#include <QString>
#include <iostream>
#include <vector>
#include <chrono>
#include <map>
#include <QDebug>

using namespace std;


/*  Globals variables    */
static bool keepPlaying = true;
static double DELTATIME;


Map::Map()
{
    this->mapScene = new QGraphicsScene();
    this->cameraView = new Scene(); // "la camera mobile"
    this->setFixedSize(500, 500);//la vue aura une taille fixe non modifiable
}

void Map::resetView(){
    delete this->mapScene;
    delete this->cameraView;
    this->mapScene = new QGraphicsScene(); // fixe
    this->cameraView = new Scene(); // "la camera mobile"
    this->setFixedSize(500, 500);//la vue aura une taille fixe non modifiable
}

void Map::initialiserScene()
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


    delete this->mapScene;
    this->mapScene = new QGraphicsScene();

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

    this->setScene(this->mapScene);
}


void Map::afficherPersonnage(Link *link)
{
    QGraphicsPixmapItem *apparencePersonnage =  new QGraphicsPixmapItem(link->getTile());
    apparencePersonnage->setPos(link->x(),link->y());

    apparencePersonnage->setZValue(100);//pour etre sur
    this->mapScene->addItem(apparencePersonnage);
}

void Map::afficherEnnemis(Ennemis *ennemi)
{
    QGraphicsPixmapItem *apparenceMechant =  new QGraphicsPixmapItem(ennemi->getTile());
    apparenceMechant->setPos(ennemi->x(),ennemi->y());

    apparenceMechant->setZValue(10);//pour etre sur
    this->mapScene->addItem(apparenceMechant);
}


//void Map::keyPressEvent(QKeyEvent *event)// je gére quand j'appuie sur une touche
//{

//     switch ( event->key())
//      {
//     case Qt::Key_Return:
//     {
//           this->controller->pressKey("enter");
//           break;
//    }
//      case Qt::Key_Right:
//      {
//            this->controller->pressKey("right");
//            break;
//     }
//      case Qt::Key_Left:
//     {
//         this->controller->pressKey("left");
//            break;
//     }
//      case Qt::Key_Down:
//           {
//         this->controller->pressKey("down");
//        break;
//     }
//      case Qt::Key_Up:
//           {this->controller->pressKey("up");
//     break;
//     }
//     case Qt::Key_A:
//     {
//         {
//             this->controller->pressKey("a");
//             break;
//         }
//     } case Qt::Key_B:
//     {
//         if(event->isAutoRepeat())
//            break;
//         else {
//             this->controller->pressKey("b");
//             break;
//         }
//     }case Qt::Key_Z:
//     {
//         if(event->isAutoRepeat())
//            break;
//         else {
//             this->controller->pressKey("z");
//             break;
//         }
//     }case Qt::Key_E:
//     {
//         if(event->isAutoRepeat())
//            break;
//         else {
//             this->controller->pressKey("e");
//             break;
//         }
//     }
//        }
//}


