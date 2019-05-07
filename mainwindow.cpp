#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "link.h"
#include "ennemie.h"
#include "zelda.h"

#include <vector>

extern std::vector<QString> currentMap;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    display_map();
    display_characters();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display_map()
{
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
}

void MainWindow::display_characters()
{
    // Link creation
    Link *link = new Link();
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
