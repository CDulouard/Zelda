#ifndef LINK_H
#define LINK_H

#include<QGraphicsPixmapItem>

class Link:public QGraphicsPixmapItem
{
public:
    Link();
    void keyPressEvent(QKeyEvent *event);
};

#endif
