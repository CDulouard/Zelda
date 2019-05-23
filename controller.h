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

    void displayStats(int health, int arrowNumber, int energy);

    void energyLoader();

    void mooveEnnemis();


protected:
    void delay(int i);

/*          attaques et Link        */
    void attack_function(QString direction);
    void checkCollisionArrowsWithEnnemis();//pour checker la collision fleche ennemie
    void mooveArrow();//pour que les flechent se deplacent

/*          Jeu et Link        */
    void game_over_procedure();
    void game_finished_procedure();

/*          objets et Link        */
    void checkCollisionEnnemis();
    void lootAleatoireDesEnnemis(class Ennemis *ennemis);
    void checkCollisionLinKZelda();

    bool checkFieldForLink(QString direction);

/*          Item et Link        */
    void checkCollisionItemsWithLink();//collision item link
    void linkRammasseUnCoeur(int i);//si zelda ramasse un coeur
    void linkRammasseUneFleche(int i);//si zelda ramasse une fleche




public slots:
    void displayScene();

private:
    Model *model;
    menu *viewMenu;
    MainWindow *viewGame;

    QTimer *timer;//raffraichissmeent de la scene

    QMediaPlayer generalSound;
    QMediaPlayer hurtSound;
    QMediaPlayer swordSound;
    QMediaPlayer bowSound;
    QMediaPlayer arrowHitSound;

    int levelCounter;
    unsigned int energyLoaderCounter;

};

#endif // CONTROLLER_H
