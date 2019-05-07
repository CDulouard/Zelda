#include "ennemie.h"

Ennemie::Ennemie()
{
    setPixmap(QPixmap(":/Character/Images/Characters/Ennemies/ennemie1.png"));
    setPos(rand()%(20)*50,rand()%(20)*50);
    this->m_health = 50;
}
