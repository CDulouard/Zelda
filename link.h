#ifndef LINK_H
#define LINK_H

#include "character.h"

class Link:public QObject,public Character
{
    Q_OBJECT

public:
    Link();

    void keyPressEvent(QKeyEvent *event);
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    void basic_assault();
    void strong_assault();
    void shoot();


//signals:
//    void change_health();
//    void change_power();
//    void change_arrow_quantity();

private:
    int _arrowQuantity;
    int _arrowDamages;
    int _swordDamages;

//    void emit_change_health();
//    void emit_change_power();
//    void emit_change_arrow_quantity();

};

#endif
