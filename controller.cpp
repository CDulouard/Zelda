#include "controller.h"
#include "mainwindow.h"
#include "menu.h"
#include "model.h"
#include "zelda.h"
#include "ennemis.h"
#include "arrow.h"

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
    this->model->getLink()->setPosX(50);
    this->model->getLink()->setPosY(50);

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
    // Lauching
    if (levelCounter == 0){
        this->viewGame->close();
        sound.setMedia(QUrl("qrc:/music/Sounds/menu_music.mp3"));
        sound.play();
        this->viewMenu->show();
    }

    //current game
    else if (levelCounter == 1){

        sound.setMedia(QUrl("qrc:/music/Sounds/game_music.mp3"));
        sound.play(); // ne marche pas

        // charger niveau
        displayScene();
        this->viewGame->show();
    }

    // Link die
    if (levelCounter == -2){
        sound.stop();
        //this->son = new QSound("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Die.wav");
        sound.play();
        //this->model->getNiveau()->chargerNiveau(); // on charge la carte correspondant au niveau
        //this->view->initialiserScene();
        //this->view->show();
    }

    // victory
    if (levelCounter == -1){
        sound.stop();
        //this->son = new QSound("/Users/alexandremagne/Desktop/Zelda2/Musiques/intro.wav");
        sound.play();
        //this->model->getNiveau()->chargerNiveau(); // on charge la carte correspondant au niveau
        //this->view->initialiserScene();
        //this->view->show();
    }
}


void Controller::displayScene(){

    this->viewGame->resetView();

    this->viewGame->displayMap();
    this->viewGame->getCameraView()->setPosX(this->model->getLink()->getPosX()-250);
    this->viewGame->getCameraView()->setPosY(this->model->getLink()->getPosY()-250);
    this->viewGame->displayLink(this->getModel()->getLink());
    //this->viewGame->afficherItemsMap(this->model->getNiveau()->getMapItems());
    if (this->viewGame->getEnnemisList().size() != 0){
        for(unsigned long i = 0; i<this->viewGame->getEnnemisList().size(); i++){
            this->viewGame->displayEnnemis(this->viewGame->getEnnemisList()[i]);
        }
    }
    this->viewGame->displayZelda(this->getModel()->getZelda());

    displayStats(this->model->getLink()->getLife(), this->model->getLink()->getArrowQuantity(), this->model->getLink()->getEnergy());

    mooveEnnemis();
    checkCollisionEnnemis();
    checkCollisionLinKZelda();

    //faireAvancerArrow(); //fais avancer la fleche et supprime l'ennemi en cas de collision

    if (this->model->getLink()->getLife() > 0)
        timer->start(20);
    else
        game_over_procedure();
}


void Controller::mooveEnnemis(){
    if (this->viewGame->getEnnemisList().size() != 0)
    {
        //this->checkCollisionEnnemis(this->viewGame->getEnnemisList()[i]);

        for (unsigned long i=0; i<this->viewGame->getEnnemisList().size(); i++){

            int randomNumber = rand()%30;
            int randomNumber2 = rand()%4;

            if(randomNumber == 0){
                switch (randomNumber2)
                {
                case (0):
                {
                    if(this->viewGame->getEnnemisList()[i]->getPosX() > 50)
                        this->viewGame->getEnnemisList()[i]->moove("left");
                    break;
                }
                case (1):
                {
                    if(this->viewGame->getEnnemisList()[i]->getPosX() < this->viewGame->currentMap[0].size()*50 -100)
                        this->viewGame->getEnnemisList()[i]->moove("right");
                    break;
                }
                case (2):
                {
                    if(this->viewGame->getEnnemisList()[i]->getPosY() > 50)
                        this->viewGame->getEnnemisList()[i]->moove("up");
                    break;
                }
                case (3):
                {
                    if(this->viewGame->getEnnemisList()[i]->getPosY() < this->viewGame->currentMap.size()*50 -100)
                        this->viewGame->getEnnemisList()[i]->moove("down");
                    break;
                }
                default:
                    break;
                }
            }
        }
    }
}

//pour checker la collision de link avec les ennemis
void Controller::checkCollisionEnnemis()
{
    if (this->viewGame->getEnnemisList().size() != 0)
    {
        for (unsigned long i=0; i<this->viewGame->getEnnemisList().size(); i++){
            if((this->viewGame->getEnnemisList()[i]->getPosX() == this->model->getLink()->getPosX()) && (this->viewGame->getEnnemisList()[i]->getPosY() == this->model->getLink()->getPosY())){
                //sound.setMedia(QUrl("un son de blessure"));
                //sound.play();
                this->model->getLink()->setLife(this->model->getLink()->getLife() - 1);

                if(this->model->getLink()->getDirection() == "left")
                    this->model->getLink()->setPosX(this->model->getLink()->getPosX() +100);

                else if(this->model->getLink()->getDirection() == "right")
                    this->model->getLink()->setPosX(this->model->getLink()->getPosX() -100);

                else if(this->model->getLink()->getDirection() == "up")
                    this->model->getLink()->setPosY(this->model->getLink()->getPosY() +100);

                else if(this->model->getLink()->getDirection() == "down")
                    this->model->getLink()->setPosY(this->model->getLink()->getPosY() -100);

            }
        }
    }
}

void Controller::checkCollisionLinKZelda()
{
    if((this->model->getLink()->getPosX() == this->model->getZelda()->getPosX()) && (this->model->getLink()->getPosY() == this->model->getZelda()->getPosY()))
        game_finished_procedure();
}


////void Controller::checkCollisionDecortWithEnnemi(Ennemis *ennemis)
//{
//    if(ennemis->getDirection()=="right"){
//            // pour la colision à droite
//        if ((this->viewGame->getMapScene()->itemAt(ennemis->getPosX()+30,ennemis->getPosY()+20, QTransform())->zValue() == 5)||(this->viewGame->getMapScene()->itemAt(ennemis->getPosX()+30, ennemis->getPosY(),QTransform())->zValue() == 5))
//        { // un mur
//            ennemis->setDirection("left");
//            this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//        }else if((this->viewGame->getMapScene()->itemAt(ennemis->getPosX()+30,ennemis->getPosY()+20, QTransform())->zValue() == 1)||(this->viewGame->getMapScene()->itemAt(ennemis->getPosX()+30, ennemis->getPosY(),QTransform())->zValue() == 1))
//        {
//            // de l'eau
//            ennemis->setDirection("left");
//            this->viewGame->getEnnemi()->deplacementEnnemis(ennemis);
//        }else {
//            this->viewGame->getEnnemi()->deplacementEnnemis(ennemis);
//        }
//    }else if (ennemis->getDirection()=="left"){
//        // pour la colision à gauche
//    if ((this->viewGame->getMapScene()->itemAt(ennemis->getPosX(),ennemis->getPosY(),QTransform())->zValue() == 5)||(this->viewGame->getMapScene()->itemAt(ennemis->getPosX()-10,ennemis->getPosY()+20,QTransform())->zValue() == 5))
//    {
//    // un mur
//        ennemis->setDirection("right");
//        this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//    }else if((this->viewGame->getMapScene()->itemAt(ennemis->getPosX(),ennemis->getPosY(),QTransform())->zValue() == 1)||(this->viewGame->getMapScene()->itemAt(ennemis->getPosX()-10,ennemis->getPosY()+20,QTransform())->zValue() == 1))
//    {
//        ennemis->setDirection("right");
//        this->viewGame->getEnnemi()->deplacementEnnemis(ennemis);
//    }else{
//        this->viewGame->getEnnemi()->deplacementEnnemis(ennemis);
//    }
//    } else if (ennemis->getDirection()=="down"){
//     // pour la colision en bas
//    if ((this->viewGame->getMapScene()->itemAt(ennemis->getPosX()+20,ennemis->getPosY()+30,QTransform())->zValue() == 5)||(this->viewGame->getMapScene()->itemAt(ennemis->getPosX(),ennemis->getPosY()+30,QTransform())->zValue() == 5))
//    {
//    // un mur
//        ennemis->setDirection("up");
//        this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//    }
//    else if ((this->viewGame->getMapScene()->itemAt(ennemis->getPosX()+20,ennemis->getPosY()+30,QTransform())->zValue() == 1)||(this->viewGame->getMapScene()->itemAt(ennemis->getPosX(),ennemis->getPosY()+30,QTransform())->zValue() == 1))
//    {
//        ennemis->setDirection("up");
//        this->viewGame->getEnnemi()->deplacementEnnemis(ennemis);
//    }else{
//        this->viewGame->getEnnemi()->deplacementEnnemis(ennemis);
//    }
//    } else if(ennemis->getDirection()=="up"){
//            // pour la colision en haut
//            if ((this->viewGame->getMapScene()->itemAt(ennemis->getPosX()+20,ennemis->getPosY()-10,QTransform())->zValue() == 5)||(this->viewGame->getMapScene()->itemAt(ennemis->getPosX(),ennemis->getPosY()-10,QTransform())->zValue() == 5))
//           {
//           // un mur
//               ennemis->setDirection("down");
//               this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//           } else if ((this->viewGame->getMapScene()->itemAt(ennemis->getPosX()+20,ennemis->getPosY()-10,QTransform())->zValue() == 1)||(this->viewGame->getMapScene()->itemAt(ennemis->getPosX(),ennemis->getPosY()-10,QTransform())->zValue() == 1))
//           {
//               ennemis->setDirection("down");
//               this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//           }else{
//               this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//           }
//    }
//}


////void Controller::lootAleatoireDesEnnemis(Ennemis *ennemis)
//{
//    if(ennemis->getType_of_monstre() == "final_boss_"){
//        //si boss final on laisse une clef par terre
//        this->model->getNiveau()->ajouterItem(ennemis->getPosX(), ennemis->getPosY(), "keyaccesslevelup" );
//    }
//    else if(ennemis->getType_of_monstre() != "lambeau_boss_niveau_2_" && ennemis->getType_of_monstre() != "boule_de_feu_"&& ennemis->getType_of_monstre() != "chauve_souris_bleu_"){
//    int v1 = rand() % 3;// si on tue un ennemi, une chance sur 5 quil laisse un coeur
//    if(v1 == 2)this->model->getNiveau()->ajouterItem(ennemis->getPosX(), ennemis->getPosY(), "heart" );
//    if(v1 == 1)this->model->getNiveau()->ajouterItem(ennemis->getPosX(), ennemis->getPosY(), "arrow_item" );
//    }
//}


////faire bouger les flèches
//void Controller::faireAvancerArrow()
//{
//    if(this->model->getNiveau()->getMapItems().size()>0){
//        for (unsigned long i=0;i<this->model->getNiveau()->getMapItems().size();i++){
//          int result = this->model->getNiveau()->getMapItems()[i]->faireAvancerFleche();//retourn 1 si on supprimer la fleche
//          if (result==1) {
//              //on supprime la fleche si == 1
//              this->model->getNiveau()->deleteItem(i);
//              return;
//          }else checkCollisionArrowsWithEnnemis();
//        }
//    }
//}



////voir si les fleches touche les ennemis
//void Controller::checkCollisionArrowsWithEnnemis()
//{
//    if (this->model->getNiveau()->getEnnemisList().size() != 0 && this->model->getNiveau()->getMapItems().size() !=0){
//        //on verifie toujours si les vecteurs existent
//        for (unsigned long i=0;i<this->model->getNiveau()->getMapItems().size();i++){
//            if (this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_right"||this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_left"||this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_down"||this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_up")
//            {//si on parle d'une Arrow (fleche)
//               for (unsigned long j = 0; j<this->model->getNiveau()->getEnnemisList().size(); j++){
//                    //pour tous les monstres on regarde si ca touche avec la fleche en question
//                   int diffX = (this->model->getNiveau()->getMapItems()[i]->getPosXactuel() - this->model->getNiveau()->getEnnemisList()[j]->getPosX());
//                   int diffY = (this->model->getNiveau()->getMapItems()[i]->getPosYactuel() - this->model->getNiveau()->getEnnemisList()[j]->getPosY());
//                   if((this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_right" && diffX<0 && diffX>-30 && diffY>-20 && diffY<20) || (this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_left" && diffX>0 && diffX<30 && diffY>-20 && diffY<20) || (this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_up" && diffX>-20 && diffX<20 && diffY>0 && diffY<30) || (this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_down" && diffX>-20 && diffX<20 && diffY<0 && diffY>-30))
//                   {
//                       QSound::play("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Hit.wav");
//                       this->model->getNiveau()->ajouterItem(this->model->getNiveau()->getEnnemisList()[j]->getPosX(),this->model->getNiveau()->getEnnemisList()[j]->getPosY(),"explosion");
//                       this->model->getNiveau()->getEnnemisList()[j]->setLifeStatue(this->model->getNiveau()->getEnnemisList()[j]->getLifeStatue()-1);
//                       this->toucheEnnemisQuandZeldaAttaque(this->model->getNiveau()->getEnnemisList()[j]);
//                       if(this->model->getNiveau()->getEnnemisList()[j]->getLifeStatue()==0){
//                          this->lootAleatoireDesEnnemis(this->model->getNiveau()->getEnnemisList()[j]);
//                           this->model->getNiveau()->deleteMonstre(j);
//                        }
//                       this->model->getNiveau()->deleteItem(i);
//                       return;
//                   }
//               }
//            }
//        }
//    }
//}

////attquer avec l'épée
//void Controller::attack_function(QString direction){
// if (this->model->getNiveau()->getEnnemisList().size() != 0){

//        for (unsigned long i = 0; i<this->model->getNiveau()->getEnnemisList().size(); i++){

//            int diffX = (this->model->getLink()->getPosX() - this->model->getNiveau()->getEnnemisList()[i]->getPosX());
//            int diffY = (this->model->getLink()->getPosY() - this->model->getNiveau()->getEnnemisList()[i]->getPosY());
//            if((direction == "right" && diffX<0 && diffX>-60 && diffY>-20 && diffY<20) || (direction == "left" && diffX>0 && diffX<50 && diffY>-20 && diffY<20) || (direction == "up" && diffX>-20 && diffX<20 && diffY>0 && diffY<50) || (direction == "down" && diffX>-20 && diffX<20 && diffY<0 && diffY>-60))
//            {
//                this->model->getNiveau()->ajouterItem(this->model->getNiveau()->getEnnemisList()[i]->getPosX(),this->model->getNiveau()->getEnnemisList()[i]->getPosY(),"explosion");
//                this->model->getNiveau()->getEnnemisList()[i]->setLifeStatue(this->model->getNiveau()->getEnnemisList()[i]->getLifeStatue()-1);
//                this->toucheEnnemisQuandZeldaAttaque(this->model->getNiveau()->getEnnemisList()[i]);
//                 QSound::play("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Hit.wav");
//                if(this->model->getNiveau()->getEnnemisList()[i]->getLifeStatue()==0){
//                   this->lootAleatoireDesEnnemis(this->model->getNiveau()->getEnnemisList()[i]);
//                    this->model->getNiveau()->deleteMonstre(i);
//                    return;
//                }
//            }
//        }
// }
//}


////void Controller::toucheEnnemisQuandZeldaAttaque(Ennemis *ennemi)
//{
//    if(ennemi->getType_of_monstre() == "final_boss_"){
//        if (ennemi->getLife() >=8 && ennemi->getLife() <=10)
//        {
//                ennemi->setSpeed(ennemi->getSpeed()+2);
//                this->model->getNiveau()->ajouterItem(ennemi->getPosX()+50,ennemi->getPosY()+100,"heart");
//                this->model->getNiveau()->ajouterItem(ennemi->getPosX()+70,ennemi->getPosY()+100,"arrow_item");
//                this->model->getNiveau()->ajouterMonstre(ennemi->getPosX(),ennemi->getPosY(),"down","boule_de_feu_");
//                this->model->getNiveau()->ajouterMonstre(ennemi->getPosX(),ennemi->getPosY(),"up","boule_de_feu_");
//                this->model->getNiveau()->ajouterMonstre(ennemi->getPosX(),ennemi->getPosY(),"right","boule_de_feu_");
//                this->model->getNiveau()->ajouterMonstre(ennemi->getPosX(),ennemi->getPosY(),"left","boule_de_feu_");
//                this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+100,ennemi->getPosY(),"down","boule_de_feu_");
//                this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()-100,ennemi->getPosY(),"up","boule_de_feu_");
//                this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+150,ennemi->getPosY(),"right","boule_de_feu_");
//                this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()-150,ennemi->getPosY(),"left","boule_de_feu_");

//        }else if  (ennemi->getLife() >=5 && ennemi->getLife() <8)
//        {
//            ennemi->setSpeed(1);
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()+30,"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()+60,"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()-30,"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()-60,"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY(),"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()+90,"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()-90,"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()+120,"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()-120,"left","boule_de_feu_");
//        }else if  (ennemi->getLife() >=3 && ennemi->getLife() <5)
//        {
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()+30,"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()+60,"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()-30,"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()-60,"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY(),"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()+90,"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()-90,"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()+120,"left","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()+200,ennemi->getPosY()-120,"left","boule_de_feu_");

//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()-200,ennemi->getPosY()+30,"right","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()-200,ennemi->getPosY()+60,"right","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()-200,ennemi->getPosY()-30,"right","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()-200,ennemi->getPosY()-60,"right","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()-200,ennemi->getPosY(),"right","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()-200,ennemi->getPosY()+90,"right","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()-200,ennemi->getPosY()-90,"right","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()-200,ennemi->getPosY()+120,"right","boule_de_feu_");
//            this->model->getNiveau()->ajouterMonstre(ennemi->getPosX()-200,ennemi->getPosY()-120,"right","boule_de_feu_");
//        }else if  (ennemi->getLife() >0 && ennemi->getLife() <3){

//        }

//    }
//}


////fonction pour check la collision de Link avec les objets sur la map
//void Controller::checkCollisionItemsWithLink()
//{
//    vector<item*> vec = this->model->getNiveau()->getMapItems();//plus simple à gérer
//    for (unsigned long i=0; i<vec.size();i++){
//    //check avec zelda et le monstre et retire des PV à zelda
//        int diffX = (this->model->getLink()->getPosX() - vec[i]->getPosXinitiale());
//        int diffY = (this->model->getLink()->getPosY() - vec[i]->getPosYinitiale());
//        if(diffX>-30 && diffX<30 && diffY<30 && diffY>-30){//si il y a collision entre l'objet et zelda
//            // si c une clef
//            if (vec[i]->getType_of_item() == "keyaccesslevelup"){
//                zeldaRammasseLaKey(i);
//                return;
//            //une vie ATTENTION on rajoute 1 a statut life zelda et non a son sac a dos EASTPACK
//            }else if(vec[i]->getType_of_item() == "heart"){
//                this->zeldaRammasseUnCoeur(i);
//                return;
//            }else if (vec[i]->getType_of_item() == "arrow_item"){
//                this->zeldaRammasseUneFleche(i);
//                return;
//            }else if(vec[i]->getType_of_item() == "sword"){
//                zeldaRammasseLaSword(i);
//                return;
//                //collision avec l'escalier
//            }else if(vec[i]->getType_of_item() == "stair_orange_niveau_1_1"){
//                this->view->getCameraView()->setPosX(200);
//                this->model->getLink()->setPosX(200);
//            }else if(vec[i]->getType_of_item() == "stair_orange_niveau_1_2"){
//                this->view->getCameraView()->setPosX(-200);
//                this->model->getLink()->setPosX(-200);
//            }else if(vec[i]->getType_of_item() == "trou_noir"){
//                this->checkObjectifNiveau();
//            }else if(vec[i]->getType_of_item() == "porteDesEnfers"){
//                this->checkObjectifNiveau();
//                return;
//            }
//        }
//    }
//}


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

    levelCounter--;
    this->startGame();
}


////void Controller::zeldaRammasseUnCoeur(int i)
//{
//    if(this->model->getLink()->getLife()<10){
//        QSound::play("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Get_Heart.wav");
//        this->model->getLink()->setLife(this->model->getLink()->getLife()+1);
//        this->model->getNiveau()->deleteItem(i);
//        return;
//    }
//}

////void Controller::zeldaRammasseUneFleche(int i)
//{
//    int compteurFleche = this->model->getLink()->arrowCounter();
//    if (compteurFleche<7){//zelda ne peut pas avoir plus de 7 fleche
//        QSound::play("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Get_Rupee.wav");
//      this->model->getLink()->ajouterItem(this->model->getNiveau()->getMapItems()[i]->getType_of_item());//on ajoute une clef a zelda
//        this->model->getNiveau()->deleteItem(i);//on supprimer la clef de la carte
//        return;
//    }
//}


void Controller::pressKey(QString key)
{
    if(levelCounter == 1)
    {
        if(key=="left")
        {
            this->model->getLink()->setTile("left");
            this->model->getLink()->setDirection("left");

            if(this->model->getLink()->getPosX() > 50)
            {
                //            if ((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX(),this->model->getLink()->getPosY(),QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX()-10,this->model->getLink()->getPosY()+this->model->getLink()->getTile().height()-10,QTransform())->zValue() == 5))
                //            {
                //                //si il ya collision avec un objet on fait rien
                //            }
                //            else{
                this->model->getLink()->moove("left");
                //            }
            }
        }

        else if(key=="right")
        {
            this->model->getLink()->setTile("right");
            this->model->getLink()->setDirection("right");

            if(this->model->getLink()->getPosX() < this->viewGame->currentMap[0].size()*50 -100)
            {
                //            //On vérifie la COLLISION
                //            if ((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX()+this->model->getLink()->getTile().width(), this->model->getLink()->getPosY()+this->model->getLink()->getTile().height()-10, QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX()+this->model->getLink()->getTile().width(), this->model->getLink()->getPosY(),QTransform())->zValue() == 5))
                //            {
                //                //si il ya collision avec un objet on fait rien
                //            }
                //            else {
                this->model->getLink()->moove("right");
                //            }
            }
        }

        else if(key == "up")
        {
            this->model->getLink()->setTile("up");
            this->model->getLink()->setDirection("up");

            if(this->model->getLink()->getPosY() > 50)
            {
                //            if ((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX()+this->model->getLink()->getTile().width()/1.5,this->model->getLink()->getPosY()-10,QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX(),this->model->getLink()->getPosY()-10,QTransform())->zValue() == 5)){
                //                //si il ya collision avec un objet on fait rien
                //            }
                //            else
                //            {
                this->model->getLink()->moove("up");
                //            }
            }

        }

        else if(key == "down")
        {
            this->model->getLink()->setTile("down");
            this->model->getLink()->setDirection("down");

            if(this->model->getLink()->getPosY() < this->viewGame->currentMap.size()*50 -100)
            {
                //            if ((this->viewGame->getMapScene()->itemAt(this->model->getZegetLinklda()->getPosX()+this->model->getLink()->getTile().width()/1.5,this->model->getLink()->getPosY()+this->model->getLink()->getTile().height(),QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX(),this->model->getLink()->getPosY()+this->model->getLink()->getTile().height(),QTransform())->zValue() == 5)){
                //                //si il ya collision avec un objet on fait rien
                //            }
                //            else{
                this->model->getLink()->moove("down");
                //            }
            }

        }


        else if(key=="h")
        {
            if(this->model->getLink()->getEnergy() > 0)
            {
                sound.setMedia(QUrl("qrc:/game/Sounds/sword_attack.mp3"));
                sound.play();
                this->model->getLink()->setEnergy(this->model->getLink()->getEnergy()-1);

                if(this->model->getLink()->getDirection() == "left"){
                    for (unsigned long i=0; i<this->viewGame->getEnnemisList().size(); i++){
                        if(this->viewGame->getEnnemisList()[i]->getPosX() == this->model->getLink()->getPosX() - 50)
                            delete this->viewGame->getEnnemisList()[i];
                            //this->viewGame->getEnnemisList().erase(this->viewGame->getEnnemisList().begin()+i);
                    }
                }

                if(this->model->getLink()->getDirection() == "right"){
                    for (unsigned long i=0; i<this->viewGame->getEnnemisList().size(); i++){
                        if(this->viewGame->getEnnemisList()[i]->getPosX() == this->model->getLink()->getPosX() + 50)
                            delete this->viewGame->getEnnemisList()[i];
                            //this->viewGame->getEnnemisList().erase(this->viewGame->getEnnemisList().begin()+i);
                    }
                }

                if(this->model->getLink()->getDirection() == "up"){
                    for (unsigned long i=0; i<this->viewGame->getEnnemisList().size(); i++){
                        if(this->viewGame->getEnnemisList()[i]->getPosY() == this->model->getLink()->getPosY() - 50)
                            delete this->viewGame->getEnnemisList()[i];
                            //this->viewGame->getEnnemisList().erase(this->viewGame->getEnnemisList().begin()+i);
                    }
                }

                if(this->model->getLink()->getDirection() == "down"){
                    for (unsigned long i=0; i<this->viewGame->getEnnemisList().size(); i++){
                        if(this->viewGame->getEnnemisList()[i]->getPosY() == this->model->getLink()->getPosY() + 50)
                            delete this->viewGame->getEnnemisList()[i];
                            //this->viewGame->getEnnemisList().erase(this->viewGame->getEnnemisList().begin()+i);
                    }
                }

            }
        }
        else if(key=="j")
        {
            if(this->model->getLink()->getArrowQuantity()>0){
                sound.setMedia(QUrl("qrc:/game/Sounds/arrow_shoot.mp3"));
                sound.play();
                this->model->getLink()->setArrowQuantity(this->model->getLink()->getArrowQuantity()-1);
                Arrow *arrow = new Arrow(this->model->getLink()->getDirection());
                arrow->setPos(x(),y());
                this->viewGame->getMapScene()->addItem(arrow);
                this->viewGame->ajouterItem(this->model->getLink()->getPosX(),this->model->getLink()->getPosY(),"arrow_"+this->model->getLink()->getDirection());
            }
        }

        else if(key == "escape")
        {
            this->sound.stop();
            viewGame->close();
            this->close();
        }
    }
    else
    {
        if (key == "enter" && levelCounter == 0)
        {
            this->sound.stop();
            viewMenu->close();
            levelCounter++;
            this->startGame();
        }
        else if(key == "escape" && levelCounter == 0)
        {
            this->sound.stop();
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
void Controller::setModel(Model *value)
{
    model = value;
}

