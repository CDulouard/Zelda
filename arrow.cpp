#include "arrow.h"
#include "link.h"

#include<QTimer>
#include <QtCore/QThread>
#include<QDebug>

extern QString lastMove;

Arrow::Arrow()
{
    setPos(x(),y());

    QTimer * timer = new QTimer;

    if (lastMove == "left"){
        connect(timer, SIGNAL(timeout()), this, SLOT(move_left()));
    }
    if (lastMove == "right"){
        connect(timer, SIGNAL(timeout()), this, SLOT(move_right()));
    }
    if (lastMove == "up"){
        connect(timer, SIGNAL(timeout()), this, SLOT(move_up()));
    }
    if (lastMove == "down"){
        connect(timer, SIGNAL(timeout()), this, SLOT(move_down()));
    }

    timer->start(50);

}

void Arrow::move_left()
{
    setPixmap(QPixmap(":/Zelda/Images/Zelda/arrow_left.png"));
    this->setPos(x()-50,y());
    arrow_life_timer++;

    if(arrow_life_timer == 7)
        delete this;
}

void Arrow::move_right()
{
    setPixmap(QPixmap(":/Zelda/Images/Zelda/arrow_right.png"));
    this->setPos(x()+50,y());
    arrow_life_timer++;

    if(arrow_life_timer == 7)
        delete this;
}

void Arrow::move_up()
{
    setPixmap(QPixmap(":/Zelda/Images/Zelda/arrow_up.png"));
    this->setPos(x(),y()-50);
    arrow_life_timer++;

    if(arrow_life_timer == 7)
        delete this;
}

void Arrow::move_down()
{
    setPixmap(QPixmap(":/Zelda/Images/Zelda/arrow_down.png"));
    this->setPos(x(),y()+50);
    arrow_life_timer++;

    if(arrow_life_timer == 7)
        delete this;
}
