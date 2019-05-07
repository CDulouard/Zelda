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
    void shoot();

private:
    int _arrows = 5;
    int _damage_arrow = 10;
    int _damage_sword = 20;

};

#endif
