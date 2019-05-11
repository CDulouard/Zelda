#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "menu.h"
#include "ui_menu.h"
#include <model.h>
#include <ennemis.h>

#include <QWidget>
#include <QObject>
#include <QTimer>
#include <QVBoxLayout>
#include <QTime>
#include <QEventLoop>
#include <QCoreApplication>
#include <QSound>

class Map;
class Controller : public QWidget
{
    Q_OBJECT

public:
    Controller(Map *view, Model *model);//constructeur
    Ui::menu *ui;

    void startGame();
    void pressKey(std::string key);

    void setModel(Model *value);
    Model *getModel() const;


protected:
    void delay(int i);
/*              zelda et element naturel                        */
    void zelda_va_dans_leau(QString direction);

/*          attaques et Zelda        */
    void attack_function(QString direction);//attaque de l'epee
    void attaque_hammer_function();//attaque du marteau
    void checkCollisionArrowsWithEnnemis();//pour checker la collision flech ennemie
    void faireAvancerArrow();//pour que les flechent se deplacent
/*          Jeu et Zelda        */
    void game_over_procedure();//en cas de game over
    void game_finished_procedure();
    void linkCircularAttack();//toutes les 2 seconde le coup du hammer
/*          Ennemis et Zelda        */
    void toucheEnnemisQuandZeldaAttaque(Ennemis *ennemi);
    void gestionApparitionExplosionToucheEnnemi();//si ya une explosion ca gere l'animation de l'explosion
    void checkCollisionEnnemis(Ennemis *ennemis);//collision zelda ennemi
    void checkCollisionDecortWithEnnemi(Ennemis *ennemis);
    void lootAleatoireDesEnnemis(Ennemis *ennemis);
    void collisionZeldaBouleDeFeu();//action quand zelda se pred une boule de feu
    void collisionZeldaLambeau();//pareil avec lambeau
/*          Item et Zelda        */
    void checkCollisionItemsWithZelda();//collision item zelda
    void zeldaRammasseUnCoeur(int i);//si zelda ramasse un coeur
    void zeldaRammasseUneFleche(int i);//si zelda ramasse une fleche
    void zeldaRammasseLaSword(int i);
    void zeldaRammasseLaKey(int i);

public slots:
    //void mooveEnnemis();
    void afficherScene();

private:
    Map *view;//represente la vue, ce que voit l'utilisateur
    Model *model;
    QTimer *timer;//raffraichissmeent de la scene
    QSound *son;
    int statueSon;//pour le son, pour le changer au niveau 2
    int linkAttaqueOuPas;//si zelda a l'animation sword ou epee , on va gerer les probleme de qpixmap null
    int niveauActuel;
    int levelCounter;




};

#endif // CONTROLLER_H
