#include "ennemis.h"
#include <QDebug>

Ennemis::Ennemis(int posXinit, int posYinit) // constructeur
{
    this->setPosX(posXinit);
    this->setPosY(posYinit);

    this->posXinitiale = posXinit;
    this->posYinitiale = posYinit;

    this->life = 3;

    this->tile = (QPixmap(":/Character/Images/Characters/Ennemies/ennemie1.png"));

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

