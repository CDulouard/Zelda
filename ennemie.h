#ifndef ENNEMIE_H
#define ENNEMIE_H

#include "Character.h"

class Ennemie:public Character
{
public:
    Ennemie();
    void move();
    void attack();

private:
    double _sante = 50;
    int _damage = 10;
};

#endif // ENNEMIE_H
