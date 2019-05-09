#include "headers.h"



void Character::Move(char x, char y, std::vector<std::string> *map, std::map<std::string, int> cellTypes)
{

}

void Character::move_left()
{
    if(this->x()-50 >= 0){
        setPos(x()-50,y());
    }
}

void Character::move_right()
{
    if(this->x()+50 < 1000){
        this->setPos(x()+50,y());
    }
}

void Character::move_up()
{
    if(this->y()-50 >=0){
        this->setPos(x(),y()-50);
    }
}

void Character::move_down()
{
    if(this->y()+50 <= 600){
        this->setPos(x(),y()+50);
    }
}

void Character::basic_assault()
{
}

float Character::get_m_health()
{
    return this->m_health;
}

void Character::set_m_health(float health)
{
    this->m_health = health;
}
