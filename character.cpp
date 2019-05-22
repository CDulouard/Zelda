#include "character.h"

Character::Character()
{
    this->posX=0;
    this->posY=0;
}

void Character::setPosX(int i)
{
    this->posX = i;
}

void Character::setPosY(int j)
{
    this->posY = j;
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

int Character::getSpeed() const
{
    return speed;
}

void Character::setSpeed(int value)
{
    speed = value;
}

QPixmap Character::getTile()
{
    return this->tile;
}
