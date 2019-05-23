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

    int getLife();
    void setLife(int life);

    int getSpeed() const;
    void setSpeed(int value);

    QString getDirection() const;
    void setDirection(const QString &value);

    QPixmap getTile();

    void moove(QString direction);


protected:
    int posX;
    int posY;
    int life;

    QPixmap tile;
    QString direction;


};

#endif // CHARACTER_H
