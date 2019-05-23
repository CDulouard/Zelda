#include "item.h"

Item::Item(int posXinit, int posYinit, QString type_of_item)
{
    this->posXinitiale=posXinit;
    this->posYinitiale=posYinit;
    this->posXactuel=posXinit;
    this->posYactuel=posYinit;
    this->type_of_item = type_of_item;
    setTile();
}

Item::Item(QString s)
{
    this->type_of_item = s;
    setTile();
}

void Item::setTile(){

    if ((this->getType_of_item() == "arrow_left") || (this->getType_of_item() == "arrow_right") || (this->getType_of_item() == "arrow_up") || (this->getType_of_item() == "arrow_down"))
        this->tile = QPixmap(":/Items/Images/Items/" + this->getType_of_item() + ".png");

    else if (this->getType_of_item() == "arrow_item")
        this->tile = QPixmap(":/Items/Images/Items/arrow_down.png");

    else
        this->tile = QPixmap(":/Items/Images/Items/" + this->getType_of_item() + ".png");
}

int Item::faireAvancerFleche()
{
    if (this->type_of_item == "arrow_right" ||this->type_of_item == "arrow_left" ||this->type_of_item == "arrow_up" ||this->type_of_item == "arrow_down"){
        int diffX = this->posXactuel - this->posXinitiale;
        int diffY = this->posYactuel - this->posYinitiale;
        //pour faire avance la fleche
        if(this->type_of_item == "arrow_right" && diffX<149){
            this->posXactuel+=10;
            return 0;
        }else  if(this->type_of_item == "arrow_left" && diffX>-149){
            this->posXactuel-=10;
            return 0;
        }else  if(this->type_of_item == "arrow_up" && diffY>-149){
            this->posYactuel-=10;
            return 0;
        }else  if(this->type_of_item == "arrow_down" && diffY<149){
            this->posYactuel+=10;
            return 0;
        }else return 1;
    }else return 0;
}



QString Item::getType_of_item() const
{
    return type_of_item;
}

void Item::setType_of_item(const QString &value)
{
    type_of_item = value;
}
int Item::getPosXinitiale() const
{
    return posXinitiale;
}

void Item::setPosXinitiale(int value)
{
    posXinitiale = value;
}
int Item::getPosYinitiale() const
{
    return posYinitiale;
}

void Item::setPosYinitiale(int value)
{
    posYinitiale = value;
}
QPixmap Item::getTile() const
{
    return tile;
}

void Item::setTile(const QPixmap &value)
{
    tile = value;
}
int Item::getPosXactuel() const
{
    return posXactuel;
}

void Item::setPosXactuel(int value)
{
    posXactuel = value;
}
int Item::getPosYactuel() const
{
    return posYactuel;
}

void Item::setPosYactuel(int value)
{
    posYactuel = value;
}
