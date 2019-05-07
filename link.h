#ifndef LINK_H
#define LINK_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "character.h"

class Link:public Character
{
public:
    Link();
    Ui::MainWindow *ui;

    void keyPressEvent(QKeyEvent *event);
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    void basic_assault();
    void strong_assault();
    void shoot();

private:
    int _arrowQuantity;
    int _arrowDamages = 25;
    int _swordDamages = 50;

};

#endif
