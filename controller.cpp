#include "controller.h"
#include "mainwindow.h"
#include "menu.h"
#include "model.h"

Controller::Controller(menu *menu, MainWindow *gameWindow, Model *model)
{
    this->model = model; // on fait le lien avec le model
    this->viewMenu = menu; // on fait le lien avec la view
    this->viewGame = gameWindow; // on fait le lien avec la view
    this->timer =  new QTimer();
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(afficherScene()));
    this->levelCounter = 0; // normalement initialiser à 0 mais là on test la game d`abord
}

void Controller::startGame()
{
    // Lauching
    if (levelCounter == 0){
        viewMenu->show();
        generalSound.setMedia(QUrl("qrc:/music/Sounds/menu_music.mp3"));
        generalSound.play(); // ne marche pas
    }

    //current game
    if (levelCounter == 1){
        generalSound.setMedia(QUrl("qrc:/music/Sounds/game_music.mp3"));
        generalSound.play(); // ne marche pas

        //on recentre link en haut a gauche a chaque niveau
        this->model->getLink()->setPosX(50);
        this->model->getLink()->setPosY(50);
        // charger niveau
        afficherScene();
        this->viewGame->show();
    }

    // Link die
    if (levelCounter == -2){
        generalSound.stop();
        //this->son = new QSound("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Die.wav");
        generalSound.play();
        //this->model->getNiveau()->chargerNiveau(); // on charge la carte correspondant au niveau
        //this->view->initialiserScene();
        //this->view->show();
    }

    // victory
    if (levelCounter == -1){
        generalSound.stop();
        //this->son = new QSound("/Users/alexandremagne/Desktop/Zelda2/Musiques/intro.wav");
        generalSound.play();
        //this->model->getNiveau()->chargerNiveau(); // on charge la carte correspondant au niveau
        //this->view->initialiserScene();
        //this->view->show();
    }
}


void Controller::afficherScene(){

    this->viewGame->displayMap();//affiche la carte
    this->viewGame->displayLink(this->getModel()->getLink());//affiche link
    //this->viewGame->afficherItemsMap(this->model->getNiveau()->getMapItems());
    //checkCollisionItemsWithZelda();
    //mooveEnnemis();//fait bouger et affiche les ennemeis
    //faireAvancerArrow();//fais avancer la fleche et supprime l'ennemi en cas de collision
    linkCircularAttack();//pour faire link attaque circulaire

    if (this->model->getLink()->getLife() > 0)
        timer->start(20);
    else
        game_over_procedure();
}

//pour faire bouger les ennemis et les afficher
//void Controller::mooveEnnemis(){
//    //pour afficher les ennemis et le boules de feu
//    if (this->model->getNiveau()->getMonstres().size() != 0){
//        for(unsigned long i = 0; i<this->model->getNiveau()->getMonstres().size(); i++)
//        {
//            this->view->afficherEnnemis(this->model->getNiveau()->getMonstres()[i]);
//        }
//    }

//    //pour faire bouger les ennemis
//    if (this->model->getNiveau()->getMonstres().size() != 0){ // si il reste encore des monstres
//        for (unsigned long i=0; i<this->model->getNiveau()->getMonstres().size(); i++){

//            this->checkCollisionEnnemis(this->model->getNiveau()->getMonstres()[i]);
//            if (this->model->getNiveau()->getMonstres().size() != 0){ // si il reste encore des monstres
//                {
//            if (this->model->getNiveau()->getMonstres()[i]->getType_of_monstre()!="boule_de_feu_" && this->model->getNiveau()->getMonstres()[i]->getType_of_monstre()!="lambeau_boss_niveau_2_")
//            {
//                this->checkCollisionDecortWithEnnemi(this->model->getNiveau()->getMonstres()[i]);
//            }
//            this->model->getNiveau()->ajouterProjectileLancerParUnMonstre(this->model->getNiveau()->getMonstres()[i]);
//            int statueProjectile = this->model->getNiveau()->getEnnemi()->deplacementProjectile(this->model->getNiveau()->getMonstres()[i]);

//            if(statueProjectile==1) {
//              this->model->getNiveau()->deleteMonstre(i);
//              return;
//            }
//                }
//        }
//    }}
//}

////pour checker la collision de zelda avec les ennemis
//void Controller::checkCollisionEnnemis(Ennemis *ennemis)
//{
//    //check avec zelda et le monstre et retire des PV à zelda
//    int diffX = (this->model->getLink()->getPosX() - ennemis->getPosX());
//    int diffY = (this->model->getLink()->getPosY() - ennemis->getPosY());

//            if ((diffX<0 && diffX>-30 && diffY>-20 && diffY<20)||(diffX>0 && diffX<20 && diffY>-20 && diffY<20)||(diffX>-20 && diffX<20 && diffY>0 && diffY<25)||(diffX>-20 && diffX<20 && diffY<0 && diffY>-20))
//            {

//                if(ennemis->getType_of_monstre()=="zelda"){
//                   ennemis->setDirection("rencontre");
//                   //this->model->getLink()->getEnnemi()->deplacementEnnemis(ennemis);
//                }

//                else{
//                    gameSound.setMedia(QUrl("un son de blessure"));
//                    gameSound.play();
//                    this->model->getLink()->setLife(this->model->getLink()->getLife() - 1);
//                    if(ennemis->getType_of_monstre() == "boule_de_feu_" ) {
//                        this->collisionZeldaBouleDeFeu();
//                    }
//                    if(ennemis->getType_of_monstre() == "lambeau_boss_niveau_2_"){
//                        this->collisionZeldaLambeau();
//                    }
//                }

//            }
//}

//void Controller::checkCollisionDecortWithEnnemi(Ennemis *ennemis)
//{
//    if(ennemis->getDirection()=="right"){
//            // pour la colision à droite
//        if ((this->view->getMapScene()->itemAt(ennemis->getPosX()+30,ennemis->getPosY()+20, QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(ennemis->getPosX()+30, ennemis->getPosY(),QTransform())->zValue() == 5))
//        { // un mur
//            ennemis->setDirection("left");
//            this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//        }else if((this->view->getMapScene()->itemAt(ennemis->getPosX()+30,ennemis->getPosY()+20, QTransform())->zValue() == 1)||(this->view->getMapScene()->itemAt(ennemis->getPosX()+30, ennemis->getPosY(),QTransform())->zValue() == 1))
//        {
//            // de l'eau
//            ennemis->setDirection("left");
//            this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//        }else {
//            this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//        }
//    }else if (ennemis->getDirection()=="left"){
//        // pour la colision à gauche
//    if ((this->view->getMapScene()->itemAt(ennemis->getPosX(),ennemis->getPosY(),QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(ennemis->getPosX()-10,ennemis->getPosY()+20,QTransform())->zValue() == 5))
//    {
//    // un mur
//        ennemis->setDirection("right");
//        this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//    }else if((this->view->getMapScene()->itemAt(ennemis->getPosX(),ennemis->getPosY(),QTransform())->zValue() == 1)||(this->view->getMapScene()->itemAt(ennemis->getPosX()-10,ennemis->getPosY()+20,QTransform())->zValue() == 1))
//    {
//        ennemis->setDirection("right");
//        this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//    }else{
//        this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//    }
//    } else if (ennemis->getDirection()=="down"){
//     // pour la colision en bas
//    if ((this->view->getMapScene()->itemAt(ennemis->getPosX()+20,ennemis->getPosY()+30,QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(ennemis->getPosX(),ennemis->getPosY()+30,QTransform())->zValue() == 5))
//    {
//    // un mur
//        ennemis->setDirection("up");
//        this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//    }
//    else if ((this->view->getMapScene()->itemAt(ennemis->getPosX()+20,ennemis->getPosY()+30,QTransform())->zValue() == 1)||(this->view->getMapScene()->itemAt(ennemis->getPosX(),ennemis->getPosY()+30,QTransform())->zValue() == 1))
//    {
//        ennemis->setDirection("up");
//        this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//    }else{
//        this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//    }
//    } else if(ennemis->getDirection()=="up"){
//            // pour la colision en haut
//            if ((this->view->getMapScene()->itemAt(ennemis->getPosX()+20,ennemis->getPosY()-10,QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(ennemis->getPosX(),ennemis->getPosY()-10,QTransform())->zValue() == 5))
//           {
//           // un mur
//               ennemis->setDirection("down");
//               this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//           } else if ((this->view->getMapScene()->itemAt(ennemis->getPosX()+20,ennemis->getPosY()-10,QTransform())->zValue() == 1)||(this->view->getMapScene()->itemAt(ennemis->getPosX(),ennemis->getPosY()-10,QTransform())->zValue() == 1))
//           {
//               ennemis->setDirection("down");
//               this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//           }else{
//               this->model->getNiveau()->getEnnemi()->deplacementEnnemis(ennemis);
//           }
//    }
//}

//void Controller::lootAleatoireDesEnnemis(Ennemis *ennemis)
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

//faire bouger les flèches
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



//voir si les fleches touche les ennemis
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

//attquer avec l'épée
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

//void Controller::attaque_hammer_function()
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


//fonction pour check la collision de Zelda avec les objets sur la map
//void Controller::checkCollisionItemsWithZelda()
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


//void Controller::zeldaRammasseUnCoeur(int i)
//{
//    if(this->model->getLink()->getLife()<10){
//        QSound::play("/Users/alexandremagne/Desktop/Zelda2/Musiques/LOZ/LOZ_Get_Heart.wav");
//        this->model->getLink()->setLife(this->model->getLink()->getLife()+1);
//        this->model->getNiveau()->deleteItem(i);
//        return;
//    }
//}

//void Controller::zeldaRammasseUneFleche(int i)
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
//    if(levelCounter == 1)
//    {
//        if(key=="right")
//        {
//            //On vérifie la COLLISION
//            if ((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX()+this->model->getLink()->getTile().width(), this->model->getLink()->getPosY()+this->model->getLink()->getTile().height()-10, QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX()+this->model->getLink()->getTile().width(), this->model->getLink()->getPosY(),QTransform())->zValue() == 5))
//            {
//                //si il ya collision avec un objet on fait rien
//            }
//            else if((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX(), this->model->getLink()->getPosY(), QTransform())->zValue() == 1)){
//                //pour nager
//                this->zelda_va_dans_leau("right");
//            }
//            else if ((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX()+30, this->model->getLink()->getPosY()+20, QTransform())->zValue() == 3)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX()+30, this->model->getLink()->getPosY(),QTransform())->zValue() == 3))
//            {
//                //si il ya collision avec les flammes de l'enfer !!!!!!

//                if (this->model->getLink()->getInvincibilité() == 0){
//                    QSound::play("/Users/alexandremagne/Desktop/zelda2/Musiques/LOZ/LOZ_Scream_Burning.wav");
//                    this->model->getLink()->setLifeStatue(this->model->getLink()->getLifeStatue() - 2); // ATTENTION ZELDA PERD 2 VIES
//                    this->model->getLink()->setInvincibilité(1);
//                    this->model->getLink()->setIsBurningOrNot(1);
//                    this->model->getLink()->getMyMonture()->setIsRidingOrNot(0);
//                    this->model->getLink()->setTilePosition(this->model->getLink()->getDirection());
//                }
//                this->model->getLink()->setIsSwimmingOrNot(0);//on indique que zelda ne nage nage pas
//                this->model->getLink()->setPosX(this->model->getLink()->getSpeed());
//                if ((this->model->getLink()->getPosX() - this->viewGame->getCameraView()->getPosX())>240)
//                    this->view->getCameraView()->setPosX(this->model->getLink()->getSpeed());
//            }else {
//                this->model->getLink()->setIsSwimmingOrNot(0);//on indique que zelda ne nage nage pas
//                this->model->getLink()->setPosX(this->model->getLink()->getSpeed());
//                if ((this->model->getLink()->getPosX() - this->viewGame->getCameraView()->getPosX())>240)
//                    this->view->getCameraView()->setPosX(this->model->getLink()->getSpeed());
//            }
//        }
//        else if(key=="left")
//        {
//            if(zeldaAttaqueOuPas == 0)this->model->getLink()->setTilePosition("left");
//            if ((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX(),this->model->getLink()->getPosY(),QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX()-10,this->model->getLink()->getPosY()+this->model->getLink()->getTile().height()-10,QTransform())->zValue() == 5))
//            {
//                //si il ya collision avec un objet on fait rien
//            }else if((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX(),this->model->getLink()->getPosY(),QTransform())->zValue() == 1))
//            {
//                //pour nager
//                this->zelda_va_dans_leau("left");
//            }else if ((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX(),this->model->getLink()->getPosY(),QTransform())->zValue() == 3)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX()-10,this->model->getLink()->getPosY()+20,QTransform())->zValue() == 3))
//            {
//                //si il ya collision avec les flammes de l'enfer !!!!!!

//                if (this->model->getLink()->getInvincibilité() == 0){
//                    QSound::play("/Users/alexandremagne/Desktop/zelda2/Musiques/LOZ/LOZ_Scream_Burning.wav");
//                    this->model->getLink()->setLifeStatue(this->model->getLink()->getLife() - 2); // ATTENTION ZELDA PERD 2 VIES
//                    this->model->getLink()->setInvincibilité(1);
//                    this->model->getLink()->setIsBurningOrNot(1);
//                    this->model->getLink()->getMyMonture()->setIsRidingOrNot(0);
//                    this->model->getLink()->setTilePosition(this->model->getLink()->getDirection());
//                }

//                this->model->getLink()->setIsSwimmingOrNot(0);//on indique que zelda ne nage nage pas
//                this->model->getLink()->setPosX(-this->model->getLink()->getSpeed());
//                if ((this->model->getLink()->getPosX() - this->viewGame->getCameraView()->getPosX())<260)
//                    this->viewGame->getCameraView()->setPosX(-this->model->getLink()->getSpeed());
//            }
//            else{
//                this->model->getLink()->setIsSwimmingOrNot(0);//on indique que zelda ne nage nage pas
//                this->model->getLink()->setPosX(-this->model->getLink()->getSpeed());
//                if ((this->model->getLink()->getPosX() - this->viewGame->getCameraView()->getPosX())<260)
//                    this->viewGame->getCameraView()->setPosX(-this->model->getLink()->getSpeed());
//            }

//        }
//        else if(key == "down")
//        {
//            if(zeldaAttaqueOuPas == 0)this->model->getLink()->setTilePosition("down");
//            if ((this->viewGame->getMapScene()->itemAt(this->model->getZegetLinklda()->getPosX()+this->model->getLink()->getTile().width()/1.5,this->model->getLink()->getPosY()+this->model->getLink()->getTile().height(),QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX(),this->model->getLink()->getPosY()+this->model->getLink()->getTile().height(),QTransform())->zValue() == 5)){
//                //si il ya collision avec un objet on fait rien
//            }else if ((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX(),this->model->getLink()->getPosY(),QTransform())->zValue() == 1))
//            {

//                //pour nager
//                this->zelda_va_dans_leau("down");

//            }
//            else if((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX()+20,this->model->getLink()->getPosY()+30,QTransform())->zValue() == 3)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX(),this->model->getLink()->getPosY()+30,QTransform())->zValue() == 3))
//            {
//                //si il ya collision avec les flammes de l'enfer !!!!!!

//                if (this->model->getLink()->getInvincibilité() == 0){
//                    QSound::play("/Users/alexandremagne/Desktop/zelda2/Musiques/LOZ/LOZ_Scream_Burning.wav");
//                    this->model->getLink()->setLifeStatue(this->model->getLink()->getLifeStatue() - 2); // ATTENTION ZELDA PERD 2 VIES
//                    this->model->getLink()->setInvincibilité(1);
//                    this->model->getLink()->setIsBurningOrNot(1);
//                    this->model->getLink()->getMyMonture()->setIsRidingOrNot(0);
//                    this->model->getLink()->setTilePosition(this->model->getLink()->getDirection());
//                }

//                this->model->getLink()->setIsSwimmingOrNot(0);//on indique que zelda ne nage nage pas
//                this->model->getLink()->setPosY(this->model->getLink()->getSpeed());
//                if ((this->model->getLink()->getPosY() - this->viewGame->getCameraView()->getPosY())>240)
//                    this->viewGame->getCameraView()->setPosY(this->model->getLink()->getSpeed());

//            }
//            else{
//                this->model->getLink()->setIsSwimmingOrNot(0);//on indique que zelda ne nage nage pas
//                this->model->getLink()->setPosY(this->model->getLink()->getSpeed());
//                if ((this->model->getLink()->getPosY() - this->viewGame->getCameraView()->getPosY())>240)
//                    this->viewGame->getCameraView()->setPosY(this->model->getLink()->getSpeed());
//            }
//        }
//        else if(key == "up")
//        {
//            if(zeldaAttaqueOuPas == 0) this->model->getLink()->setTilePosition("up");
//            if ((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX()+this->model->getLink()->getTile().width()/1.5,this->model->getLink()->getPosY()-10,QTransform())->zValue() == 5)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX(),this->model->getLink()->getPosY()-10,QTransform())->zValue() == 5)){
//                //si il ya collision avec un objet on fait rien
//            }else if ((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX(),this->model->getLink()->getPosY(),QTransform())->zValue() == 1))
//            {
//                //zelda nage
//                this->zelda_va_dans_leau("up");

//            }else if ((this->viewGame->getMapScene()->itemAt(this->model->getLink()->getPosX()+20,this->model->getLink()->getPosY()-10,QTransform())->zValue() == 3)||(this->view->getMapScene()->itemAt(this->model->getLink()->getPosX(),this->model->getLink()->getPosY()-10,QTransform())->zValue() == 3))
//            {
//                //si il ya collision avec les flammes de l'enfer !!!!!!

//                if (this->model->getLink()->getInvincibilité() == 0){
//                    QSound::play("/Users/alexandremagne/Desktop/zelda2/Musiques/LOZ/LOZ_Scream_Burning.wav");
//                    this->model->getLink()->setLifeStatue(this->model->getLink()->getLifeStatue() - 2); // ATTENTION ZELDA PERD 2 VIES
//                    this->model->getLink()->setInvincibilité(1);
//                    this->model->getLink()->setIsBurningOrNot(1);
//                    this->model->getLink()->getMyMonture()->setIsRidingOrNot(0);
//                    this->model->getLink()->setTilePosition(this->model->getLink()->getDirection());
//                }

//                this->model->getLink()->setIsSwimmingOrNot(0);//on indique que zelda ne nage nage pas
//                this->model->getLink()->setPosY(-this->model->getLink()->getSpeed());
//                if ((this->model->getLink()->getPosY() - this->view->getCameraView()->getPosY())<260)
//                    this->viewGame->getCameraView()->setPosY(-this->model->getLink()->getSpeed());
//            }
//            else
//            {
//                this->model->getLink()->setIsSwimmingOrNot(0);//on indique que zelda ne nage nage pas
//                this->model->getLink()->setPosY(-this->model->getLink()->getSpeed());
//                if ((this->model->getLink()->getPosY() - this->viewGame->getCameraView()->getPosY())<260)
//                    this->viewGame->getCameraView()->setPosY(-this->model->getLink()->getSpeed());
//            }
//        }
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
//    }
//    else
    {
        if (key == "enter" && levelCounter == 0)
        {
            qDebug() << "enter2";
            this->generalSound.stop();
            viewMenu->close();
            levelCounter++;
            this->startGame();
        }
        else if(key == "enter" && levelCounter == 0)
        {
            this->generalSound.stop();
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

