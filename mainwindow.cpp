#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "link.h"
#include "map.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        QGraphicsScene *scene = new QGraphicsScene();
        ui->graphicsView->setScene(scene);


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
