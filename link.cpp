#include "link.h"


Link::Link()
{
    this->lifeMax = 3;
    this->setLife(3);
    this->arrowQuantityMax = 3;
    this->setArrowQuantity(3);
    this->energyMax = 3;
    this->setEnergy(3);
    this->direction = "down";
    this->tile = QPixmap(":/Character/Images/Characters/Link/link_down.png");
    this->setPosX(11*50);
    this->setPosY(7*50);
}

int Link::getArrowQuantity() const
{
    return arrowQuantity;
}

void Link::setArrowQuantity(int value)
{
    arrowQuantity = value;
}

int Link::getEnergy() const
{
    return energy;
}

void Link::setEnergy(int value)
{
    energy = value;
}

int Link::getLifeMax() const
{
    return lifeMax;
}

int Link::getEnergyMax() const
{
    return energyMax;
}

int Link::getArrowQuantityMax() const
{
    return arrowQuantityMax;
}

void Link::setTile(QString direction)
{

    if(direction=="right"||direction=="left"||direction=="up"||direction=="down")
        this->tile=QPixmap(":/Character/Images/Characters/Link/link_"+direction+".png");
    this->direction = direction;

}
