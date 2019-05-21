#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class Character
{
public:
    Character();

    int getPosX();
    void setPosX(int i);

    int getPosY();
    void setPosY(int j);

    float getLife();
    void setLife(int life);

    int getSpeed() const;
    void setSpeed(int value);

    QPixmap getTile();


protected:
    int posX;
    int posY;
    int life;
    int speed;

    QPixmap tile;
    float m_energy;
    float m_power; /*  amount of damages the character deals  */
    double m_range;  /*  max distance of a a hit */   // inutile je pense

};

#endif // CHARACTER_H
