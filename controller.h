#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <QObject>
#include <QWidget>
#include <QMediaPlayer>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>


class Map;
class Controller : public QWidget
{
    Q_OBJECT

public:
    Controller(class menu *menu, class MainWindow *gameWindow, class Model *model);
    ~Controller();

    void startGame();
    void pressKey(QString key);

    void setModel(Model *value);
    Model *getModel() const;

    void mooveEnnemis();


protected:
    void delay(int i);

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
    void toucheEnnemisQuandZeldaAttaque(class Ennemis *ennemi);
    void checkCollisionEnnemis(Ennemis *ennemis);
    void checkCollisionDecortWithEnnemi(Ennemis *ennemis);
    void lootAleatoireDesEnnemis(Ennemis *ennemis);

/*          Item et Zelda        */
    void checkCollisionItemsWithLink();//collision item link
    void zeldaRammasseUnCoeur(int i);//si zelda ramasse un coeur
    void zeldaRammasseUneFleche(int i);//si zelda ramasse une fleche
    void zeldaRammasseLaSword(int i);
    void zeldaRammasseLaKey(int i);

public slots:
    //void mooveEnnemis();
    void displayScene();

private:
    //represente la vue, ce que voit l'utilisateur
    menu *viewMenu;
    MainWindow *viewGame;

    // le model
    Model *model;

    QTimer *timer;//raffraichissmeent de la scene
    QMediaPlayer sound;

    int levelCounter;




};

#endif // CONTROLLER_H
