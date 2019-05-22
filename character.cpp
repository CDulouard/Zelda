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

QPixmap Character::getTile()
{
    return this->tile;
}

QString Character::getDirection() const
{
    return direction;
}

void Character::setDirection(const QString &value)
{
    direction = value;
}

void Character::moove(QString direction)
{
    if(direction == "left"){
        this->setPosX(this->getPosX()-50);
    }
    else if(direction == "right"){
        this->setPosX(this->getPosX()+50);
    }
    else if(direction == "up"){
        this->setPosY(this->getPosY()-50);
    }
    else if(direction == "down"){
        this->setPosY(this->getPosY()+50);
    }
}
