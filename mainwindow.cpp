#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "link.h"
#include "Map.h"
#include "QDebug"

#include <vector>

extern std::vector<QString> currentMap;
QString lastMove = "right";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        QGraphicsScene *scene = new QGraphicsScene();
        ui->graphicsView->setScene(scene);
         ui->graphicsView->centerOn(0,0);


        for (unsigned int i = 0 ; i < currentMap.size() ; i++) {
            for (unsigned int j = 0 ; j < currentMap.size() ; j++){

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

        Link *zelda = new Link();
        zelda->setPixmap(QPixmap(":/Zelda/Images/Zelda/zelda.png"));
        scene -> addItem(zelda);
        zelda->setFlag(QGraphicsItem::ItemIsFocusable);
        zelda->setFocus();



}

MainWindow::~MainWindow()
{
    delete ui;
}
