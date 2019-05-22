#ifndef ENNEMIS_H
#define ENNEMIS_H

#include "character.h"
#include <QString>

class Ennemis:public Character
{
public:
    Ennemis(int posXinit, int posYinit);

    int getPosXinitiale() const;
    void setPosXinitiale(int value);

    int getPosYinitiale() const;
    void setPosYinitiale(int value);

    int getSpeed() const;
    void setSpeed(int value);

private:
    int posXinitiale;
    int posYinitiale;

};

#endif // ENNEMIE_H
