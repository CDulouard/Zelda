#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "link.h"
#include "ennemie.h"
#include "zelda.h"

#include <vector>

extern std::vector<QString> currentMap;
QString lastMove = "right";

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        QGraphicsScene *scene = new QGraphicsScene();
        ui->graphicsView->setScene(scene);


        for (unsigned int i = 0 ; i < currentMap.size() ; i++) {
            for (unsigned int j = 0 ; j < 20 ; j++){

                if (currentMap[i][j] == "0"){
                    QGraphicsPixmapItem *grass = new QGraphicsPixmapItem();
                    grass->setPixmap(QPixmap(":/terrain/Images/Terrain/Grass.jpg"));
                    grass->setPos(j*50,i*50);
                    scene -> addItem(grass);
                }
                if (currentMap[i][j] == "x"){
                    QGraphicsPixmapItem *wall = new QGraphicsPixmapItem();
                    wall->setPixmap(QPixmap(":/terrain/Images/Terrain/wall.jpg"));
                    wall->setPos(j*50,i*50);
                    scene -> addItem(wall);
                }
            }
        }

        // Link creation

        Link *link = new Link();
        link->setPixmap(QPixmap(":/Character/Images/Characters/Link/link_left.png"));
        link->setPos(50,50);
        scene -> addItem(link);
        link->setFlag(QGraphicsItem::ItemIsFocusable);
        link->setFocus();

        // Zelda creation
        Zelda *zelda = new Zelda();
        scene -> addItem(zelda);

        // ennemies creation

        for (int i = 0; i < rand()%(10-4) +4 ; i++){
            Ennemie *mob = new Ennemie();
            scene -> addItem(mob);
        }





}

MainWindow::~MainWindow()
{
    delete ui;
}
