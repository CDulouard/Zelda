#include "loot_heal.h"

Loot_Heal::Loot_Heal(double x, double y)
{
    this-> setPixmap(QPixmap(":/Character/Images/Characters/heart.png"));
    this->setPos(x,y);
    /*  un truc comme ça
    health = link->get_m_health();
    health += 20;
    link->set_m_health(health);
    */

}
