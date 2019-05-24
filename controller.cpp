#include "controller.h"
#include "mainwindow.h"
#include "menu.h"
#include "model.h"
#include "zelda.h"
#include "ennemis.h"

#include <QDebug>
#include <QSplashScreen>

Controller::Controller(menu *menu, MainWindow *gameWindow, Model *model)
{
    this->model = model; // on fait le lien avec le model
    this->viewMenu = menu; // on fait le lien avec la view
    this->viewGame = gameWindow; // on fait le lien avec la view
    this->timer =  new QTimer();
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(displayScene()));
    this->levelCounter = 0;
    this->eventCounter = 0;

    this->hurtSound.setMedia(QUrl("qrc:/game/Sounds/link_hurt.mp3"));
    this->swordSound.setMedia(QUrl("qrc:/game/Sounds/sword_attack.mp3"));
    this->bowSound.setMedia(QUrl("qrc:/game/Sounds/arrow_shoot.mp3"));
    this->arrowHitSound.setMedia(QUrl("qrc:/game/Sounds/arrow_hit.mp3"));

}

Controller::~Controller()
{
    delete this->model;
    delete this->viewMenu;
    delete this->viewGame;
}

void Controller::delay(int i)//attend un nombre de MS
{
    QTime dieTime= QTime::currentTime().addMSecs(i);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Controller::startGame()
{
    this->model->getZelda()->setPosX((this->viewGame->getCurrentMap()[0].size() - 12) * 50);
    this->model->getZelda()->setPosY(int(this->viewGame->getCurrentMap().size() - 8) * 50);


    // Lauching
    if (levelCounter == 0){
        this->viewGame->close();
        generalSound.setMedia(QUrl("qrc:/music/Sounds/menu_music.mp3"));
        generalSound.play();
        this->viewMenu->show();
    }

    //current game
    else if (levelCounter == 1){
        generalSound.stop();
        generalSound.setMedia(QUrl("qrc:/music/Sounds/game_music.mp3"));
        generalSound.play();

        // charger niveau
        displayScene();
        this->viewGame->show();
    }
}


void Controller::displayScene(){

    eventCounter++;

    this->viewGame->resetView();
    this->viewGame->displayMap();
    this->viewGame->getCameraView()->setPosX(this->model->getLink()->getPosX()-250);
    this->viewGame->getCameraView()->setPosY(this->model->getLink()->getPosY()-250);
    this->viewGame->displayMapItems(this->viewGame->getMapItems());
    if (this->viewGame->getEnnemisList().size() != 0){
        for(unsigned long i = 0; i<this->viewGame->getEnnemisList().size(); i++){
            this->viewGame->displayEnnemis(this->viewGame->getEnnemisList()[i]);
        }
    }
    this->viewGame->displayLink(this->getModel()->getLink());
    this->viewGame->displayZelda(this->getModel()->getZelda());
    displayStats(int(this->model->getLink()->getLife()), this->model->getLink()->getArrowQuantity(), this->model->getLink()->getEnergy());

    if(eventCounter%150 == 0){
        energyLoader();
        itemDeleter();
    }

    mooveArrow();
    mooveEnnemis();
    checkCollisionEnnemisArrows();
    checkCollisionLinkEnnemis();
    checkCollisionLinKZelda();
    checkCollisionLinkItems();


    if (this->model->getLink()->getLife() > 0)
        timer->start(20);
    else
        game_over_procedure();
}


void Controller::mooveEnnemis(){
    if (this->viewGame->getEnnemisList().size() != 0)
    {
        for (unsigned long i=0; i<this->viewGame->getEnnemisList().size(); i++){

            int randomNumber = rand()%30;
            int randomNumber2 = rand()%4;

            if(randomNumber == 0){
                switch (randomNumber2)
                {
                case (0): // left
                {
                    if(checkCollisionEnnemisEnnemis("left", int(i))){
                        QCharRef string1 = this->viewGame->getCurrentMap()[this->viewGame->getEnnemisList()[i]->getPosY()/50][this->viewGame->getEnnemisList()[i]->getPosX()/50 - 1];
                        QString caseToMoveOn = QString(string1);
                        if(this->viewGame->getCellTypes()[caseToMoveOn])
                            this->viewGame->getEnnemisList()[i]->moove("left");
                    }
                    break;
                }
                case (1): // right
                {
                    if(checkCollisionEnnemisEnnemis("right", int(i))){
                        QCharRef string1 = this->viewGame->getCurrentMap()[this->viewGame->getEnnemisList()[i]->getPosY()/50][this->viewGame->getEnnemisList()[i]->getPosX()/50 + 1];
                        QString caseToMoveOn = QString(string1);
                        if(this->viewGame->getCellTypes()[caseToMoveOn])
                            this->viewGame->getEnnemisList()[i]->moove("right");
                    }
                    break;
                }
                case (2): // up
                {
                    if(checkCollisionEnnemisEnnemis("up", int(i))){
                        QCharRef string1 = this->viewGame->getCurrentMap()[this->viewGame->getEnnemisList()[i]->getPosY()/50 - 1][this->viewGame->getEnnemisList()[i]->getPosX()/50];
                        QString caseToMoveOn = QString(string1);
                        if(this->viewGame->getCellTypes()[caseToMoveOn])
                            this->viewGame->getEnnemisList()[i]->moove("up");
                    }
                    break;
                }
                case (3): // down
                {
                    if(checkCollisionEnnemisEnnemis("down", int(i))){
                        QCharRef string1 = this->viewGame->getCurrentMap()[this->viewGame->getEnnemisList()[i]->getPosY()/50 + 1][this->viewGame->getEnnemisList()[i]->getPosX()/50];
                        QString caseToMoveOn = QString(string1);
                        if(this->viewGame->getCellTypes()[caseToMoveOn])
                            this->viewGame->getEnnemisList()[i]->moove("down");
                    }
                    break;
                }
                default:
                    break;
                }
            }
        }
    }
}


void Controller::checkCollisionLinkEnnemis()
{
    if (this->viewGame->getEnnemisList().size() != 0)
    {
        for (unsigned long i=0; i<this->viewGame->getEnnemisList().size(); i++){
            if((this->viewGame->getEnnemisList()[i]->getPosX() == this->model->getLink()->getPosX()) && (this->viewGame->getEnnemisList()[i]->getPosY() == this->model->getLink()->getPosY())){
                hurtSound.play();
                this->model->getLink()->setLife(int(this->model->getLink()->getLife()) - 1);

                if(this->model->getLink()->getDirection() == "left")
                    this->model->getLink()->setPosX(this->model->getLink()->getPosX() +50);

                else if(this->model->getLink()->getDirection() == "right")
                    this->model->getLink()->setPosX(this->model->getLink()->getPosX() -50);

                else if(this->model->getLink()->getDirection() == "up")
                    this->model->getLink()->setPosY(this->model->getLink()->getPosY() +50);

                else if(this->model->getLink()->getDirection() == "down")
                    this->model->getLink()->setPosY(this->model->getLink()->getPosY() -50);

            }
        }
    }
}

void Controller::checkCollisionLinKZelda()
{
    if((this->model->getLink()->getPosX() == this->model->getZelda()->getPosX()) && (this->model->getLink()->getPosY() == this->model->getZelda()->getPosY()))
    {
        this->model->getLink()->setPosX(this->model->getZelda()->getPosX() - 50);
        this->model->getLink()->setPosY(this->model->getZelda()->getPosY());
        this->model->getLink()->setTile("down");

        if(this->viewGame->getEnnemisList().size() == 0)
            game_finished_procedure();
    }
}



bool Controller::checkFieldForLink(QString direction)
{
    if(direction == "left"){
        QCharRef string1 = this->viewGame->getCurrentMap()[this->model->getLink()->getPosY()/50][this->model->getLink()->getPosX()/50 - 1];
        QString caseToMoveOn = QString(string1);
        return this->viewGame->getCellTypes()[caseToMoveOn];
    }

    else if(direction == "right"){
        QCharRef string1 = this->viewGame->getCurrentMap()[this->model->getLink()->getPosY()/50][this->model->getLink()->getPosX()/50 + 1];
        QString caseToMoveOn = QString(string1);
        return this->viewGame->getCellTypes()[caseToMoveOn];
    }

    if(direction == "up"){
        QCharRef string1 = this->viewGame->getCurrentMap()[this->model->getLink()->getPosY()/50 -1][this->model->getLink()->getPosX()/50];
        QString caseToMoveOn = QString(string1);
        return this->viewGame->getCellTypes()[caseToMoveOn];
    }

    if(direction == "down"){
        QCharRef string1 = this->viewGame->getCurrentMap()[this->model->getLink()->getPosY()/50 + 1][this->model->getLink()->getPosX()/50];
        QString caseToMoveOn = QString(string1);
        return this->viewGame->getCellTypes()[caseToMoveOn];
    }
    return 0;
}


void Controller::itemDeleter()
{
    for(unsigned int i = 0 ; i < this->viewGame->getMapItems().size(); i++){
        this->viewGame->getMapItems()[i]->setItemLifeCounter(this->viewGame->getMapItems()[i]->getItemLifeCounter() - 1);

        if(this->viewGame->getMapItems()[i]->getItemLifeCounter() == 0)
            this->viewGame->deleteItem(int(i));
    }
}


void Controller::lootAleatoireDesEnnemis(Ennemis *ennemis)
{
    int randomNumber = rand() % 5 + 1;

    if(randomNumber == 1)
        this->viewGame->ajouterItem(ennemis->getPosX(), ennemis->getPosY(), "heart" );

    else if(randomNumber == 2)
        this->viewGame->ajouterItem(ennemis->getPosX(), ennemis->getPosY(), "arrow_item" );

    else
        this->viewGame->ajouterItem(ennemis->getPosX(), ennemis->getPosY(), "empty" );
}


//faire bouger les flèches
void Controller::mooveArrow()
{
    if(this->viewGame->getMapItems().size()>0){
        for (unsigned long i=0;i<this->viewGame->getMapItems().size();i++){
            if (this->viewGame->getMapItems()[i]->getType_of_item() == "arrow_left")
                this->viewGame->getMapItems()[i]->setPosXactuel(this->viewGame->getMapItems()[i]->getPosXactuel() - 50);

            else if (this->viewGame->getMapItems()[i]->getType_of_item() == "arrow_right")
                this->viewGame->getMapItems()[i]->setPosXactuel(this->viewGame->getMapItems()[i]->getPosXactuel() + 50);

            else if (this->viewGame->getMapItems()[i]->getType_of_item() == "arrow_up")
                this->viewGame->getMapItems()[i]->setPosYactuel(this->viewGame->getMapItems()[i]->getPosYactuel() - 50);

            else if (this->viewGame->getMapItems()[i]->getType_of_item() == "arrow_down")
                this->viewGame->getMapItems()[i]->setPosYactuel(this->viewGame->getMapItems()[i]->getPosYactuel() + 50);
        }
    }
}



//voir si les fleches touche les ennemis
void Controller::checkCollisionEnnemisArrows()
{
    if (this->viewGame->getEnnemisList().size() > 0 && this->viewGame->getMapItems().size() > 0){

        for (unsigned long i=0;i<this->viewGame->getMapItems().size();i++){
            if (this->viewGame->getMapItems()[i]->getType_of_item() == "arrow_right"||this->viewGame->getMapItems()[i]->getType_of_item() == "arrow_left"||this->viewGame->getMapItems()[i]->getType_of_item() == "arrow_down"||this->viewGame->getMapItems()[i]->getType_of_item() == "arrow_up")
            {
                for (unsigned long j = 0; j<this->viewGame->getEnnemisList().size(); j++){

                    if((this->viewGame->getMapItems()[i]->getPosXactuel() == this->viewGame->getEnnemisList()[j]->getPosX()) && (this->viewGame->getMapItems()[i]->getPosYactuel() == this->viewGame->getEnnemisList()[j]->getPosY())){
                        this->arrowHitSound.play();
                        this->lootAleatoireDesEnnemis(this->viewGame->getEnnemisList()[j]);
                        this->viewGame->deleteMonster(int(j));
                        this->viewGame->deleteItem(int(i));
                    }
                }
            }
        }
    }
}

//this->viewGame->getEnnemisList()[nbMonster]->getPosX() == this->viewGame->getEnnemisList()[j]->getPosX() +50

bool Controller::checkCollisionEnnemisEnnemis(QString direction, int nbMonster)
{
    if(this->viewGame->getEnnemisList().size() > 1){

        for(unsigned int j = 0 ; j < this->viewGame->getEnnemisList().size() ; j++){
            if(direction == "left"){
                if((this->viewGame->getEnnemisList()[nbMonster]->getPosY() != this->viewGame->getEnnemisList()[j]->getPosY()) || (this->viewGame->getEnnemisList()[nbMonster]->getPosY() == this->viewGame->getEnnemisList()[j]->getPosY() && this->viewGame->getEnnemisList()[nbMonster]->getPosX() != this->viewGame->getEnnemisList()[j]->getPosX() + 50))
                    return true;
            }

            else if(direction == "right"){
                if((this->viewGame->getEnnemisList()[nbMonster]->getPosY() != this->viewGame->getEnnemisList()[j]->getPosY()) || (this->viewGame->getEnnemisList()[nbMonster]->getPosY() == this->viewGame->getEnnemisList()[j]->getPosY() && this->viewGame->getEnnemisList()[nbMonster]->getPosX() != this->viewGame->getEnnemisList()[j]->getPosX() - 50))
                    return true;
            }

            else if(direction == "up"){
                if((this->viewGame->getEnnemisList()[nbMonster]->getPosX() != this->viewGame->getEnnemisList()[j]->getPosX()) || (this->viewGame->getEnnemisList()[nbMonster]->getPosX() == this->viewGame->getEnnemisList()[j]->getPosX() && this->viewGame->getEnnemisList()[nbMonster]->getPosY() != this->viewGame->getEnnemisList()[j]->getPosY() + 50))
                    return true;
            }

            else if(direction == "down"){
                if((this->viewGame->getEnnemisList()[nbMonster]->getPosX() != this->viewGame->getEnnemisList()[j]->getPosX()) || (this->viewGame->getEnnemisList()[nbMonster]->getPosX() == this->viewGame->getEnnemisList()[j]->getPosX() && this->viewGame->getEnnemisList()[nbMonster]->getPosY() != this->viewGame->getEnnemisList()[j]->getPosY() - 50))
                    return true;
            }

            else
                return false;
        }
    }
    return false;
}


void Controller::attack_function(QString direction){
    if (this->viewGame->getEnnemisList().size() != 0){

        for (unsigned long i=0; i<this->viewGame->getEnnemisList().size(); i++){

            if((direction == "left") && (this->viewGame->getEnnemisList()[i]->getPosX() == this->model->getLink()->getPosX() - 50) && (this->viewGame->getEnnemisList()[i]->getPosY() == this->model->getLink()->getPosY())){

                this->lootAleatoireDesEnnemis(this->viewGame->getEnnemisList()[i]);
                this->viewGame->deleteMonster(int(i));
            }

            else if((direction == "right") && (this->viewGame->getEnnemisList()[i]->getPosX() == this->model->getLink()->getPosX() + 50) && (this->viewGame->getEnnemisList()[i]->getPosY() == this->model->getLink()->getPosY())){

                this->lootAleatoireDesEnnemis(this->viewGame->getEnnemisList()[i]);
                this->viewGame->deleteMonster(int(i));
            }

            else if((direction == "up") && (this->viewGame->getEnnemisList()[i]->getPosY() == this->model->getLink()->getPosY() - 50) && (this->viewGame->getEnnemisList()[i]->getPosX() == this->model->getLink()->getPosX())){

                this->lootAleatoireDesEnnemis(this->viewGame->getEnnemisList()[i]);
                this->viewGame->deleteMonster(int(i));
            }

            else if((direction == "down") && (this->viewGame->getEnnemisList()[i]->getPosY() == this->model->getLink()->getPosY() + 50) && (this->viewGame->getEnnemisList()[i]->getPosX() == this->model->getLink()->getPosX())){

                this->lootAleatoireDesEnnemis(this->viewGame->getEnnemisList()[i]);
                this->viewGame->deleteMonster(int(i));
            }
        }
    }
}


void Controller::checkCollisionLinkItems()
{
    for (unsigned long i=0; i<this->viewGame->getMapItems().size();i++){

        if((this->model->getLink()->getPosX() == this->viewGame->getMapItems()[i]->getPosXactuel()) && (this->model->getLink()->getPosY() == this->viewGame->getMapItems()[i]->getPosYactuel())){

            if(this->viewGame->getMapItems()[i]->getType_of_item() == "heart"){
                if(this->model->getLink()->getLife()<this->model->getLink()->getLifeMax()){
                    //QSound::play("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Get_Heart.wav");
                    this->model->getLink()->setLife(this->model->getLink()->getLife()+1);
                    this->viewGame->deleteItem(int(i));
                    return;
                }
            }

            else if (this->viewGame->getMapItems()[i]->getType_of_item() == "arrow_item"){
                if(this->model->getLink()->getArrowQuantity()<this->model->getLink()->getArrowQuantityMax()){
                    //QSound::play("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Get_Heart.wav");
                    this->model->getLink()->setArrowQuantity(this->model->getLink()->getArrowQuantity()+1);
                    this->viewGame->deleteItem(int(i));
                    return;
                }
            }
        }
    }
}


void Controller::game_over_procedure()
{
    timer->stop();
    qDebug()<<"game over";

    //Add Splash Screen
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/Menu/Images/game-over.jpg"));
    splash->show();
    delay(2000);
    splash->close();

    this->viewGame->resetView();
    this->viewGame->mapGenerator();
    this->model->resetModel();

    levelCounter--;
    this->startGame();
}

void Controller::game_finished_procedure()
{
    timer->stop();
    qDebug()<<"game finished";

    //Add Splash Screen
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/Menu/Images/victory.jpg"));
    splash->show();
    delay(2000);
    splash->close();

    this->viewGame->resetView();
    this->viewGame->mapGenerator();
    this->model->resetModel();

    levelCounter--;
    this->startGame();
}


void Controller::pressKey(QString key)
{
    if(levelCounter == 1)
    {
        if(key=="left")
        {
            this->model->getLink()->setTile("left");
            this->model->getLink()->setDirection("left");

            if(checkFieldForLink(key))
            {
                this->model->getLink()->moove("left");
            }
        }

        else if(key=="right")
        {
            this->model->getLink()->setTile("right");
            this->model->getLink()->setDirection("right");

            if(checkFieldForLink(key))
            {
                this->model->getLink()->moove("right");
            }
        }

        else if(key == "up")
        {
            this->model->getLink()->setTile("up");
            this->model->getLink()->setDirection("up");

            if(checkFieldForLink(key))
            {
                this->model->getLink()->moove("up");
            }

        }

        else if(key == "down")
        {
            this->model->getLink()->setTile("down");
            this->model->getLink()->setDirection("down");

            if(checkFieldForLink(key))
            {
                this->model->getLink()->moove("down");
            }

        }


        else if(key=="h")
        {
            if(this->model->getLink()->getEnergy() > 0)
            {
                swordSound.play();
                this->model->getLink()->setEnergy(this->model->getLink()->getEnergy()-1);
                this->attack_function(this->model->getLink()->getDirection());
            }
        }
        else if(key=="j")
        {
            if(this->model->getLink()->getArrowQuantity()>0){
                bowSound.play();
                this->model->getLink()->setArrowQuantity(this->model->getLink()->getArrowQuantity()-1);
                this->viewGame->ajouterItem(this->model->getLink()->getPosX(),this->model->getLink()->getPosY(),"arrow_"+this->model->getLink()->getDirection());
            }
        }

        else if(key == "escape")
        {
            this->generalSound.stop();
            viewGame->close();
            this->close();
        }
    }
    else
    {
        if (key == "enter" && levelCounter == 0)
        {
            this->generalSound.stop();
            viewMenu->close();
            levelCounter++;
            this->startGame();
        }
        else if(key == "escape" && levelCounter == 0)
        {
            this->generalSound.stop();
            viewMenu->close();
            this->close();
        }
    }
}

Model *Controller::getModel() const
{
    return model;
}

void Controller::displayStats(int health, int arrowNumber, int energy)
{
    this->viewGame->displayStats(health, arrowNumber, energy);
}

void Controller::energyLoader()
{
    if(this->model->getLink()->getEnergy() < this->model->getLink()->getEnergyMax())
        this->model->getLink()->setEnergy(this->model->getLink()->getEnergy() + 1);
}
void Controller::setModel(Model *value)
{
    model = value;
}
