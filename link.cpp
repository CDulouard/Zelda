#include "link.h"


Link::Link()
{
    this->setPosX(0);
    this->setPosY(0);
    this->setLife(8);
    this->direction = "down";
    this->tile = QPixmap(":/Character/Images/Characters/Link/link_down.png"); //image par défaut
    this->isAmoradoOrNot = 0;
    this->LoadingCircularAttack = 250;
}

int Link::arrowCounter()
{
    return _arrowQuantity;
}


int Link::getNumber() const
{
    return number;
}

void Link::setNumber(int value)
{
    number = value;
}
QString Link::getDirection() const
{
    return direction;
}

void Link::setDirection(const QString &value)
{
    direction = value;
}

int Link::getSpeed() const
{
    return speed;
}

void Link::setSpeed(int value)
{
    speed = value;
}

int Link::getLoadingCircularAttack() const
{
    return LoadingCircularAttack;
}

void Link::setLoadingCircularAttack(int value)
{
    LoadingCircularAttack = value;
}

int Link::getIsAmoradoOrNot() const
{
    return isAmoradoOrNot;
}

void Link::setIsAmoradoOrNot(int value)
{
    isAmoradoOrNot = value;
}

