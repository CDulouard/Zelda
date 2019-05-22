#include "ennemis.h"
#include <QDebug>

Ennemis::Ennemis(int posXinit, int posYinit) // constructeur
{
    this->setPosX(posXinit);
    this->setPosY(posYinit);

    this->posXinitiale = posXinit;
    this->posYinitiale = posYinit;

    this->speed = 50;
    this->life = 3;

    this->tile = (QPixmap(":/Character/Images/Characters/Ennemies/ennemie1.png"));

}


// fonction appelée toute les 20 ms
void Ennemis::mooveEnnemis(QString direction)
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


int Ennemis::getPosXinitiale() const
{
    return posXinitiale;
}

void Ennemis::setPosXinitiale(int value)
{
    posXinitiale = value;
    setPosX(value);
}
int Ennemis::getPosYinitiale() const
{
    return posYinitiale;
}

void Ennemis::setPosYinitiale(int value)
{
    posYinitiale = value;
    setPosY(value);
}

int Ennemis::getSpeed() const
{
    return speed;
}

void Ennemis::setSpeed(int value)
{
    speed = value;
}
