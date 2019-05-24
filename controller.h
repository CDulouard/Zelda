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

protected:
    void delay(int i);
    void itemDeleter();

    void displayStats(int health, int arrowNumber, int energy);
    void energyLoader();
    void mooveEnnemis();

    void attack_function(QString direction);

    void mooveArrow();

    void lootAleatoireDesEnnemis(class Ennemis *ennemis);

    void checkCollisionLinkItems();
    void checkCollisionLinkEnnemis();
    void checkCollisionLinKZelda();

    bool checkFieldForLink(QString direction);

    void checkCollisionEnnemisArrows();
    bool checkCollisionEnnemisEnnemis(QString direction, int nbMonster);

    void game_over_procedure();
    void game_finished_procedure();


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
    unsigned int eventCounter;

};

#endif // CONTROLLER_H
