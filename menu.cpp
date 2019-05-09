#include "headers.h"

#include<QMediaPlayer>


menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);

    setFixedSize(1500,844);
    setWindowIcon(QIcon(":/icons/Images/Icones/Zelda.png"));
    setWindowTitle("Zelda");

    QMediaPlayer *music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/menu/Sounds/menu_music.mp3"));
    music->play();
    music->stop();


    QPixmap bkgnd(":/Menu/Images/menu_background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);


    connect(ui->playButton, SIGNAL(pressed()), this, SLOT(openGameWindow()));


}

menu::~menu()
{
    delete ui;
}

void menu::openGameWindow()
{
    MainWindow * gameWindow = new MainWindow();
    gameWindow->show();
    this->close();
}

