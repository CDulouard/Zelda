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

    int getLifeMax() const;
    int getEnergyMax() const;
    int getArrowQuantityMax() const;

    void shoot();


private:
    int lifeMax;
    int arrowQuantity;
    int arrowQuantityMax;
    int energy;
    int energyMax;



};

#endif
