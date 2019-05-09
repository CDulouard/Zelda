#include "headers.h"

Ennemie::Ennemie()
{
    setPixmap(QPixmap(":/Character/Images/Characters/Ennemies/ennemie1.png"));
    setPos(rand()%(20)*50,rand()%(20)*50);
    this->m_health = 50;
    this->m_speed = 1;
    this->m_power = 20;
    this->m_range = 1;
}

void Ennemie::die()
{
    Loot_Heal *loot = new Loot_Heal(this->x(), this->y());
    delete this;
}
