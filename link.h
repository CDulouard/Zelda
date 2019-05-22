#ifndef LINK_H
#define LINK_H

#include "character.h"

class Link:public QObject,public Character
{

public:
    Link();

    QString getlastMove();
    void setlastMove(QString lastMove);

    void setTile(QString direction);

    int getArrowQuantity() const;
    void setArrowQuantity(int value);

    int getEnergy() const;
    void setEnergy(int value);

    void shoot();


private:
    int arrowQuantity = 5;
    int energy = 3;



};

#endif
