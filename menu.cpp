#include "headers.h"


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

    // Sound
    _menuMusic.setMedia(QUrl("qrc:/menu/Sounds/menu_music.mp3"));
    _menuMusic.play();

    connect(ui->playButton, SIGNAL(pressed()), this, SLOT(openGameWindow()));

}

menu::~menu()
{
    delete ui;
}

void menu::openGameWindow()
{
    MainWindow * gameWindow = new MainWindow();
    _menuMusic.stop();
    gameWindow->show();
    this->close();
}

