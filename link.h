#ifndef LINK_H
#define LINK_H

#include "character.h"

class Link:public QObject,public Character
{
    Q_OBJECT

public:
    Link();

    int arrowCounter();//pour savoir le nombre de fleche de zelda

    QString getlastMove();
    void setlastMove(QString lastMove);

    int getNumber() const;
    void setNumber(int value);

    QString getDirection() const;
    void setDirection(const QString &value);

    int getSpeed() const;
    void setSpeed(int value);

    int getLoadingCircularAttack() const;
    void setLoadingCircularAttack(int value);


    int getIsAmoradoOrNot() const;
    void setIsAmoradoOrNot(int value);

//    void keyPressEvent(QKeyEvent *event);
//    void strong_assault();
//    void shoot();


private:
    int _arrowQuantity = 5;
//    int _arrowDamages = 25;
//    int _swordDamages = 50;
//    QString _lastMove = "right";

    int number;//pour la position de l'image
    QString direction;
    int speed;

    int isAmoradoOrNot;//pour quand zelda touche zelda
    int LoadingCircularAttack;//pour savoir si zelda peut utiliser ou non le marteau (on va dire 10 seconde de recharge)



};

#endif
