#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class Character
{
public:
    Character();
    void setPosX(int i);
    void setPosY(int j);
    void setLife(int life);
    int getPosX();
    int getPosY();
    float getLife();
    QPixmap getTile();

protected:
    int posX;
    int posY;
    int life;

    QPixmap tile;
    float m_energy;
    float m_power; /*  amount of damages the character deals  */
    double m_range;  /*  max distance of a a hit */   // inutile je pense
    float m_speed;

};

#endif // CHARACTER_H
