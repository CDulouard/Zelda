#include "link.h"
#include "arrow.h"
#include "mainwindow.h"

#include<QKeyEvent>
#include<QDebug>
#include<QGraphicsScene>

Link::Link()
{
}

QString Link::get_lastMove() const
{
    return _lastMove;
}

void Link::set_lastMove(QString lastMove)
{
_lastMove = lastMove;
}

void Link::keyPressEvent(QKeyEvent *event)
{
    // Movements

    if ((event->key() == Qt::Key_Left) || (event->key() == Qt::Key_A)){
        this->setPixmap(QPixmap(":/Zelda/Images/Zelda/zelda.png"));
        setPos(x()-50,y());
        set_lastMove("left");
        qDebug() << get_lastMove();
    }

    if ((event->key() == Qt::Key_Right) || (event->key() == Qt::Key_D)){
        this->setPixmap(QPixmap(":/Zelda/Images/Zelda/zelda_right.png"));
        setPos(x()+50,y());
        set_lastMove("right");
        qDebug() << get_lastMove();
    }

    if ((event->key() == Qt::Key_Up) || (event->key() == Qt::Key_W)){
        setPos(x(),y()-50);
        set_lastMove("up");
        qDebug() << get_lastMove();
    }

    if ((event->key() == Qt::Key_Down) || (event->key() == Qt::Key_S)){
        setPos(x(),y()+50);
        set_lastMove("down");
        qDebug() << get_lastMove();
    }

    // Attacks

    if (event->key() == Qt::Key_H){
        // attaque de base
    }

    if (event->key() == Qt::Key_J){
        // attaque puissante. tout autour. consomme energie
    }

    if ((event->key() == Qt::Key_K) || (event->key() == Qt::Key_Space)){
        Arrow *arrow = new Arrow();
        arrow->setPos(x(),y());
        scene()->addItem(arrow);


    }

}
