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


//signals:
//    void change_health();
//    void change_power();
//    void change_arrow_quantity();

private:
    int _arrowQuantity = 5;
    int _arrowDamages = 25;
    int _swordDamages = 50;
    QString _lastMove = "right";

//    void emit_change_health();
//    void emit_change_power();
//    void emit_change_arrow_quantity();

};

#endif
