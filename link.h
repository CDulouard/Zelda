#ifndef LINK_H
#define LINK_H

#include<QGraphicsPixmapItem>

class Link:public QGraphicsPixmapItem
{
public:
    Link();
    QString get_lastMove() const;
    void set_lastMove(QString);
    void keyPressEvent(QKeyEvent *event);

private:
    QString _lastMove = "right";

};

#endif
