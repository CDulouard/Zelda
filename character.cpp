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

//void Character::move_left()
//{
//    if(this->x()-50 >= 0){
//        setPos(x()-50,y());
//    }
//}

//void Character::move_right()
//{
//    if(this->x()+50 < 1000){
//        this->setPos(x()+50,y());
//    }
//}

//void Character::move_up()
//{
//    if(this->y()-50 >=0){
//        this->setPos(x(),y()-50);
//    }
//}

//void Character::move_down()
//{
//    if(this->y()+50 <= 600){
//        this->setPos(x(),y()+50);
//    }
//}

//void Character::basic_assault()
//{
//}



