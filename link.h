#ifndef LINK_H
#define LINK_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Character.h"

class Link:public Character
{
public:
    Link();
    void keyPressEvent(QKeyEvent *event);
    Ui::MainWindow *ui;

private:
    double _health = 100;
    double _energy = 100;
    int _arrows = 5;
    int _damage_arrow = 10;
    int _damage_sword = 20;

};

#endif
