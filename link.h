#ifndef LINK_H
#define LINK_H

#include "character.h"

class Link:public QObject,public Character
{
    Q_OBJECT

public:
    Link();

    void keyPressEvent(QKeyEvent *event);
    void strong_assault();
    void shoot();
    QString get_lastMove();
    void set_lastMove(QString lastMove);

private:
    int _arrowQuantity = 5;
    int _arrowDamages = 25;
    int _swordDamages = 50;
    QString _lastMove = "right";


};

#endif
