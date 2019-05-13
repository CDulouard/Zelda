#include "character.h"

Character::Character()
{
    this->posX=0;
    this->posY=0;
}

void Character::setPosX(int i)
{
    if ((i+this->posX)<0)
        return;
    else if ((i+this->posX)>1480)
        return;
    else
        this->posX = i+this->posX;
}

void Character::setPosY(int j)
{
    if ((j+this->posY)<0)
        return;
    else if ((j+this->posY)>730)
        return;
    else
        this->posY = j+this->posY;

}

int Character::getPosX()
{
    return this->posX;
}

int Character::getPosY()
{
    return this->posY;
}

void Character::setLife(int life)
{
    this->life=life;//si la vie passe en dessous de 0 on met à 0
}

float Character::getLife()
{
    return this->life;
}

QPixmap Character::getTile()
{
    return this->tile;
}
