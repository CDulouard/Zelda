#ifndef ARROW_H
#define ARROW_H

#include<QGraphicsPixmapItem>

class Arrow:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Arrow();

public slots:
    void move_left();
    void move_right();
    void move_up();
    void move_down();

private:
    int arrow_life_timer = 0;

};

#endif // ARROW_H
