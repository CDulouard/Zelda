#include "link.h"


Link::Link()
{
    this->setLife(5);
    this->setArrowQuantity(5);
    this->setEnergy(3);
    this->setPosX(11*50);
    this->setPosY(7*50);
    this->direction = "down";
    this->tile = QPixmap(":/Character/Images/Characters/Link/link_down.png");
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

void Link::setTile(QString direction)
{

    if(direction=="right"||direction=="left"||direction=="up"||direction=="down")
        this->tile=QPixmap(":/Character/Images/Characters/Link/link_"+direction+".png");
    this->direction = direction;

}
