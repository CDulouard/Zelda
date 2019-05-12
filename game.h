#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <link.h>
#include <QGraphicsScene>
#include <scene.h>

#include <QMainWindow>
#include<QMediaPlayer>

#include "model.h"
#include "ennemis.h"

#include <QWidget>
#include <QMediaPlayer>

class MainWindow;
class Map;
class Controller;
class Model;
class menu;

class Controller : public QWidget
{
    Q_OBJECT

public:

    Controller(menu *menu, MainWindow *gameWindow, Model *model);//constructeur
    menu *ui;

    void startGame();
    void pressKey(QString key);

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
    //represente la vue, ce que voit l'utilisateur
    menu *viewMenu;
    MainWindow *viewGame;

    // le model
    Model *model;

    QTimer *timer;//raffraichissmeent de la scene
    QMediaPlayer son;

    int levelCounter;




};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resetView();

    void displayMap();
    void displayLink(Link *link);
    void keyPressEvent(QKeyEvent *event);

private:
    MainWindow *ui;
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsScene *mapScene;   // scene ou carte
    Scene *cameraView;          // camera

    std::vector<QString> currentMap;
    std::map<QString, int> cellTypes;

    Controller *controller;

};



class menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

    MainWindow *getMainwindow() const;

    int getLevelCounter() const;
    void setLevelCounter(int newCounter);

    int getPlayButtonPressedOrNot() const;
    void setPlayButtonPressedOrNot(int newValue);

public slots:
    int playButtonPressed();

protected:
    menu *ui;
    QMediaPlayer menuMusic;
    int playButtonPressedOrNot;
};



#endif // GAME_H
