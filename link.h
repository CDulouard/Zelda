#ifndef LINK_H
#define LINK_H

#include "character.h"

class Link:public QObject,public Character
{

public:
    Link();

    int arrowCounter();

    QString getlastMove();
    void setlastMove(QString lastMove);

    int getNumber() const;
    void setNumber(int value);

    QString getDirection() const;
    void setDirection(const QString &value);

    void setTile(QString direction);

    int getLoadingCircularAttack() const;
    void setLoadingCircularAttack(int value);


    int getIsAmoradoOrNot() const;
    void setIsAmoradoOrNot(int value);

    void strong_assault();
    void shoot();


private:
    int _arrowQuantity = 5;
//    int _arrowDamages = 25;
//    int _swordDamages = 50;
//    QString _lastMove = "right";

    int number;//pour la position de l'image
    QString direction;

    int isAmoradoOrNot;//pour quand zelda touche zelda
    int LoadingCircularAttack;//pour savoir si zelda peut utiliser ou non le marteau (on va dire 10 seconde de recharge)



};

#endif
