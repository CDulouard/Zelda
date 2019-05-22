#include "controller.h"
#include "mainwindow.h"
#include "menu.h"
#include "model.h"
#include "ennemis.h"

#include <QDebug>

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

void Controller::startGame()
{
    // Lauching
    if (levelCounter == 0){
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

    if (this->viewGame->getMonstres().size() != 0){
        for(unsigned long i = 0; i<this->viewGame->getMonstres().size(); i++)
        {
            this->viewGame->displayEnnemis(this->viewGame->getMonstres()[i]);
        }
    }

    mooveEnnemis();

    //this->viewGame->afficherItemsMap(this->model->getNiveau()->getMapItems());

    //checkCollisionItemsWithZelda();

    //faireAvancerArrow(); //fais avancer la fleche et supprime l'ennemi en cas de collision

    if (this->model->getLink()->getLife() > 0)
        timer->start(20);
    else
        game_over_procedure();
}


void Controller::mooveEnnemis(){
    if (this->viewGame->getMonstres().size() != 0)
    {
        //this->checkCollisionEnnemis(this->viewGame->getMonstres()[i]);

        for (unsigned long i=0; i<this->viewGame->getMonstres().size(); i++){

            int randomNumber = rand()%30;
            int randomNumber2 = rand()%4;

            if(randomNumber == 0){
                switch (randomNumber2)
                {
                case (0):
                {
                    if(this->viewGame->getMonstres()[i]->getPosX() > 50)
                        this->viewGame->getMonstres()[i]->mooveEnnemis("left");
                    break;
                }
                case (1):
                {
                    if(this->viewGame->getMonstres()[i]->getPosX() < this->viewGame->currentMap[0].size()*50 -100)
                        this->viewGame->getMonstres()[i]->mooveEnnemis("right");
                    break;
                }
                case (2):
                {
                    if(this->viewGame->getMonstres()[i]->getPosY() > 50)
                        this->viewGame->getMonstres()[i]->mooveEnnemis("up");
                    break;
                }
                case (3):
                {
                    if(this->viewGame->getMonstres()[i]->getPosY() < this->viewGame->currentMap.size()*50 -100)
                        this->viewGame->getMonstres()[i]->mooveEnnemis("down");
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
void Controller::checkCollisionEnnemis(Ennemis *ennemis)
{
    //check avec link et le monstre et retire des PV à zelda
    int diffX = (this->model->getLink()->getPosX() - ennemis->getPosX());
    int diffY = (this->model->getLink()->getPosY() - ennemis->getPosY());

            if ((diffX<0 && diffX>-30 && diffY>-20 && diffY<20)||(diffX>0 && diffX<20 && diffY>-20 && diffY<20)||(diffX>-20 && diffX<20 && diffY>0 && diffY<25)||(diffX>-20 && diffX<20 && diffY<0 && diffY>-20))
            {

//                if(ennemis->getType_of_monstre()=="zelda"){
//                   ennemis->setDirection("rencontre");
//                   //this->model->getLink()->getEnnemi()->deplacementEnnemis(ennemis);
//                }

//                else{
//                    sound.setMedia(QUrl("un son de blessure"));
//                    sound.play();
                    this->model->getLink()->setLife(this->model->getLink()->getLife() - 1);
//                }

            }
}


//void Controller::checkCollisionDecortWithEnnemi(Ennemis *ennemis)
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
//    if (this->model->getNiveau()->getMonstres().size() != 0 && this->model->getNiveau()->getMapItems().size() !=0){
//        //on verifie toujours si les vecteurs existent
//        for (unsigned long i=0;i<this->model->getNiveau()->getMapItems().size();i++){
//            if (this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_right"||this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_left"||this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_down"||this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_up")
//            {//si on parle d'une Arrow (fleche)
//               for (unsigned long j = 0; j<this->model->getNiveau()->getMonstres().size(); j++){
//                    //pour tous les monstres on regarde si ca touche avec la fleche en question
//                   int diffX = (this->model->getNiveau()->getMapItems()[i]->getPosXactuel() - this->model->getNiveau()->getMonstres()[j]->getPosX());
//                   int diffY = (this->model->getNiveau()->getMapItems()[i]->getPosYactuel() - this->model->getNiveau()->getMonstres()[j]->getPosY());
//                   if((this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_right" && diffX<0 && diffX>-30 && diffY>-20 && diffY<20) || (this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_left" && diffX>0 && diffX<30 && diffY>-20 && diffY<20) || (this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_up" && diffX>-20 && diffX<20 && diffY>0 && diffY<30) || (this->model->getNiveau()->getMapItems()[i]->getType_of_item() == "arrow_down" && diffX>-20 && diffX<20 && diffY<0 && diffY>-30))
//                   {
//                       QSound::play("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Hit.wav");
//                       this->model->getNiveau()->ajouterItem(this->model->getNiveau()->getMonstres()[j]->getPosX(),this->model->getNiveau()->getMonstres()[j]->getPosY(),"explosion");
//                       this->model->getNiveau()->getMonstres()[j]->setLifeStatue(this->model->getNiveau()->getMonstres()[j]->getLifeStatue()-1);
//                       this->toucheEnnemisQuandZeldaAttaque(this->model->getNiveau()->getMonstres()[j]);
//                       if(this->model->getNiveau()->getMonstres()[j]->getLifeStatue()==0){
//                          this->lootAleatoireDesEnnemis(this->model->getNiveau()->getMonstres()[j]);
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
// if (this->model->getNiveau()->getMonstres().size() != 0){

//        for (unsigned long i = 0; i<this->model->getNiveau()->getMonstres().size(); i++){

//            int diffX = (this->model->getLink()->getPosX() - this->model->getNiveau()->getMonstres()[i]->getPosX());
//            int diffY = (this->model->getLink()->getPosY() - this->model->getNiveau()->getMonstres()[i]->getPosY());
//            if((direction == "right" && diffX<0 && diffX>-60 && diffY>-20 && diffY<20) || (direction == "left" && diffX>0 && diffX<50 && diffY>-20 && diffY<20) || (direction == "up" && diffX>-20 && diffX<20 && diffY>0 && diffY<50) || (direction == "down" && diffX>-20 && diffX<20 && diffY<0 && diffY>-60))
//            {
//                this->model->getNiveau()->ajouterItem(this->model->getNiveau()->getMonstres()[i]->getPosX(),this->model->getNiveau()->getMonstres()[i]->getPosY(),"explosion");
//                this->model->getNiveau()->getMonstres()[i]->setLifeStatue(this->model->getNiveau()->getMonstres()[i]->getLifeStatue()-1);
//                this->toucheEnnemisQuandZeldaAttaque(this->model->getNiveau()->getMonstres()[i]);
//                 QSound::play("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Hit.wav");
//                if(this->model->getNiveau()->getMonstres()[i]->getLifeStatue()==0){
//                   this->lootAleatoireDesEnnemis(this->model->getNiveau()->getMonstres()[i]);
//                    this->model->getNiveau()->deleteMonstre(i);
//                    return;
//                }
//            }
//        }
// }
//}

////void Controller::attaque_hammer_function()
//{
//  {
//        this->model->getLink()->setZeldaRechargeAttaqueHammerOuPas(0);//pour remettre le compteur
//        this->model->getNiveau()->ajouterItem(this->model->getLink()->getPosX()-15,this->model->getLink()->getPosY()-10,"hammer_hole");
//        if (this->model->getNiveau()->getMonstres().size() != 0){

//               for (unsigned long i = 0; i<this->model->getNiveau()->getMonstres().size(); i++){

//                   int diffX = (this->model->getLink()->getPosX() - this->model->getNiveau()->getMonstres()[i]->getPosX());
//                   int diffY = (this->model->getLink()->getPosY() - this->model->getNiveau()->getMonstres()[i]->getPosY());
//                   if(diffX<100 && diffX>-100 && diffY>-100 && diffY<100)
//                   {
//                       this->model->getNiveau()->ajouterItem(this->model->getNiveau()->getMonstres()[i]->getPosX(),this->model->getNiveau()->getMonstres()[i]->getPosY(),"explosion");
//                       this->model->getNiveau()->getMonstres()[i]->setLifeStatue(this->model->getNiveau()->getMonstres()[i]->getLifeStatue()-2);
//                       this->toucheEnnemisQuandZeldaAttaque(this->model->getNiveau()->getMonstres()[i]);
//                        QSound::play("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Hit.wav");
//                       if(this->model->getNiveau()->getMonstres()[i]->getLifeStatue()<=0){
//                          this->lootAleatoireDesEnnemis(this->model->getNiveau()->getMonstres()[i]);
//                           this->model->getNiveau()->deleteMonstre(i);
//                          this->attaque_hammer_function();
//                          return;
//                       }
//                   }
//               }
//        }
//    }
//}


void Controller::linkCircularAttack()
{
    if(this->model->getLink()->getLoadingCircularAttack() < 250){
        this->model->getLink()->setLoadingCircularAttack(this->model->getLink()->getLoadingCircularAttack() +1);
    }else return;
}

//void Controller::toucheEnnemisQuandZeldaAttaque(Ennemis *ennemi)
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


////fonction pour check la collision de Zelda avec les objets sur la map
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


//fonction appelee quand zelda n'a plus de vie
void Controller::game_over_procedure()
{
         qDebug()<<"game over";
         timer->stop();
         this->viewGame->resetView();
         this->model->resetModel();
         this->startGame();
}

void Controller::game_finished_procedure()
    {
             qDebug()<<"game finished";
             timer->stop();
             this->viewGame->resetView();
             this->model->resetModel();
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

            if(this->model->getLink()->getPosX() > 50)
            {
                //            if ((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX(),this->model->getLink()->getPosY(),QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX()-10,this->model->getLink()->getPosY()+this->model->getLink()->getTile().height()-10,QTransform())->zValue() == 5))
                //            {
                //                //si il ya collision avec un objet on fait rien
                //            }
                //            else{
                this->model->getLink()->setPosX(this->model->getLink()->getPosX() - this->model->getLink()->getSpeed());
                //this->viewGame->getCameraView()->setPosX(this->model->getLink()->getPosX() - this->model->getLink()->getSpeed());
                //            }
            }
        }

        else if(key=="right")
        {
            this->model->getLink()->setTile("right");

            if(this->model->getLink()->getPosX() < this->viewGame->currentMap[0].size()*50 -100)
            {
                //            //On vérifie la COLLISION
                //            if ((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX()+this->model->getLink()->getTile().width(), this->model->getLink()->getPosY()+this->model->getLink()->getTile().height()-10, QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX()+this->model->getLink()->getTile().width(), this->model->getLink()->getPosY(),QTransform())->zValue() == 5))
                //            {
                //                //si il ya collision avec un objet on fait rien
                //            }
                //            else {
                this->model->getLink()->setPosX(this->model->getLink()->getPosX() + this->model->getLink()->getSpeed());
                //this->viewGame->getCameraView()->setPosX(this->model->getLink()->getSpeed());
                //            }
            }
        }

        else if(key == "up")
        {
            this->model->getLink()->setTile("up");
            if(this->model->getLink()->getPosY() > 50)
            {
                //            if ((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX()+this->model->getLink()->getTile().width()/1.5,this->model->getLink()->getPosY()-10,QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX(),this->model->getLink()->getPosY()-10,QTransform())->zValue() == 5)){
                //                //si il ya collision avec un objet on fait rien
                //            }
                //            else
                //            {
                this->model->getLink()->setPosY(this->model->getLink()->getPosY() - this->model->getLink()->getSpeed());
                //this->viewGame->getCameraView()->setPosY(this->model->getLink()->getPosY() - this->model->getLink()->getSpeed());
                //            }
            }

        }

        else if(key == "down")
        {
            this->model->getLink()->setTile("down");
            if(this->model->getLink()->getPosY() < this->viewGame->currentMap.size()*50 -100)
            {
                //            if ((this->viewGame->getMapScene()->itemAt(this->model->getZegetLinklda()->getPosX()+this->model->getLink()->getTile().width()/1.5,this->model->getLink()->getPosY()+this->model->getLink()->getTile().height(),QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX(),this->model->getLink()->getPosY()+this->model->getLink()->getTile().height(),QTransform())->zValue() == 5)){
                //                //si il ya collision avec un objet on fait rien
                //            }
                //            else{
                this->model->getLink()->setPosY(this->model->getLink()->getPosY() + this->model->getLink()->getSpeed());
                //this->viewGame->getCameraView()->setPosY(this->model->getLink()->getPosY() + this->model->getLink()->getSpeed());
                //            }
            }

        }


//        else if(key=="h")
//        {
//            if(this->model->getLink()->getSword()!=NULL){
//                QSound::play("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Sword.wav");
//                this->model->getLink()->setNumber(1);
//                this->attack_function(this->model->getLink()->getDirection());
//                zeldaAttaqueOuPas=1;
//                for(int i = 0;i<6;i++){

//                    this->model->getLink()->setTilePosition("a");
//                    delay(25);
//                }
//                zeldaAttaqueOuPas=0;
//                this->model->getLink()->setNumber(1);
//                this->model->getLink()->getMyMonture()->setIsRidingOrNot(0);
//                this->model->getLink()->setTilePosition(this->model->getLink()->getDirection());
//            }
//        }
//        else if(key=="j")
//        {
//            if(this->model->getLink()->compteurDeFleche()>0){
//                QSound::play("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Arrow.wav");
//                this->model->getLink()->deleteItem("arrow_item");
//                this->model->getNiveau()->ajouterItem(this->model->getLink()->getPosX(),this->model->getLink()->getPosY(),"arrow_"+this->model->getLink()->getDirection());
//                //QSound::play("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Sword.wav");
//                this->model->getLink()->setNumber(1);
//                // this->attack_function(this->model->getLink()->getDirection());
//                zeldaAttaqueOuPas=1;
//                for(int i = 0;i<6;i++){
//                    this->model->getLink()->setTilePosition("z");
//                    delay(25);
//                }
//                zeldaAttaqueOuPas=0;
//                this->model->getLink()->setNumber(1);//pour affichage
//                this->model->getLink()->getMyMonture()->setIsRidingOrNot(0);//pour supprimer la monture, pour pas quil remonte sur le cheval
//                this->model->getLink()->setTilePosition(this->model->getLink()->getDirection());//pour affichage zelda
//            }
//        }
//        else if(key=="k" &&  this->model->getLink()->getLoadingCircularAttack() == 250)
//        {
//            this->model->getLink()->setNumber(1);
//            this->zeldaAttaqueOuPas=1;

//            for(int i = 0;i<12;i++){
//                this->model->getLink()->setTilePosition("e");
//                delay(50);
//            }QSound::play("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Hammer.wav");
//            this->attaque_hammer_function();
//            zeldaAttaqueOuPas=0;
//            this->model->getLink()->setNumber(1);//pour affichage
//            this->model->getLink()->getMyMonture()->setIsRidingOrNot(0);//pour supprimer la monture, pour pas quil remonte sur le cheval
//            this->model->getLink()->setTilePosition(this->model->getLink()->getDirection());//pour affichage zelda

//        }
//        else if(key == "b" && zeldaAttaqueOuPas == 0  && this->check_quete()==0)
//        {
//            if(this->model->getLink()->getMyMonture()!=NULL){//si il y a une monture
//                this->model->getLink()->setNumber(1);//pour remettre a 0 le compteur dimage
//                if (this->model->getLink()->getMyMonture()->getIsRidingOrNot() == 0)//si pas montee
//                    this->model->getLink()->getMyMonture()->setIsRidingOrNot(1);//on le monte
//                else this->model->getLink()->getMyMonture()->setIsRidingOrNot(0);//sinon on le decen
//                this->model->getLink()->setTilePosition(this->model->getLink()->getDirection());//on affiche link
//            }
//        }
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




void Controller::delay(int i)//attend un nombre de MS
{
    QTime dieTime= QTime::currentTime().addMSecs(i);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


Model *Controller::getModel() const
{
    return model;
}
void Controller::setModel(Model *value)
{
    model = value;
}

