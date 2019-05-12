#include "menu.h"
#include "ui_menu.h"
#include "mainwindow.h"


menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);

    this->playButtonPressedOrNot = 0;

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

    // Sound
    menuMusic.setMedia(QUrl("qrc:/menu/Sounds/menu_music.mp3"));

    connect(ui->playButton, SIGNAL(pressed()), this, SLOT(playButtonPressed()));

}

menu::~menu()
{
    delete ui;
}

int menu::getPlayButtonPressedOrNot() const
{
    return playButtonPressedOrNot;
}

void menu::setPlayButtonPressedOrNot(int newValue)
{
    this->playButtonPressedOrNot = newValue;
}


int menu::playButtonPressed()
{
    // renvoit au controller
    //this->close();
    //startGame
    setPlayButtonPressedOrNot(1);
    return playButtonPressedOrNot;
}

