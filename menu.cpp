#include "menu.h"
#include "ui_menu.h"
#include "controller.h"

#include <QKeyEvent>
#include <QDebug>

extern Controller *pointeurControlleur;

menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);

    // window's general options
    setFixedSize(1500,844);
    setWindowIcon(QIcon(":/icons/Images/Icones/Zelda.png"));
    setWindowTitle("Zelda");

    // Background
    QPixmap bkgnd(":/Menu/Images/menu_background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

}

menu::~menu()
{
    delete ui;
}

void menu::keyPressEvent(QKeyEvent *event)
{
    switch ( event->key())
    {
    case Qt::Key_Escape:
    {
        pointeurControlleur->pressKey("escape");
        break;
    }
    case Qt::Key_P:
    {
        pointeurControlleur->pressKey("enter");
        break;
    }
    }
}
