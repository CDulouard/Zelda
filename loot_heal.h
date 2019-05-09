#ifndef LOOT_HEAL_H
#define LOOT_HEAL_H

#include<QGraphicsPixmapItem>

class Loot_Heal:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT


public:
    Loot_Heal(double x, double y);

};

#endif
