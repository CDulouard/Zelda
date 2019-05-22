#ifndef ZELDA_H
#define ZELDA_H


#include "character.h"

class Zelda:public QObject,public Character
{
public:
    Zelda();
};

#endif // ZELDA_H
