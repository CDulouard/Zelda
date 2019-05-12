#include "arrow.h"

#include<QTimer>
#include <QtCore/QThread>
#include<QMediaPlayer>
//extern QString lastMove;

Arrow::Arrow(QString lastMove)
{
    QMediaPlayer *arrow_shoot = new QMediaPlayer();
    arrow_shoot->setMedia(QUrl("qrc:/arrow/Sounds/arrow_shoot.mp3"));
    arrow_shoot->play();

    setPos(x(),y());
    QTimer * timer = new QTimer;

    if (lastMove == "left"){
        connect(timer, SIGNAL(timeout()), this, SLOT(move_left()));
    }
    else if (lastMove == "right"){
        connect(timer, SIGNAL(timeout()), this, SLOT(move_right()));
    }
    else if (lastMove == "up"){
        connect(timer, SIGNAL(timeout()), this, SLOT(move_up()));
    }
    else if (lastMove == "down"){
        connect(timer, SIGNAL(timeout()), this, SLOT(move_down()));
    }

    timer->start(50);

}

void Arrow::move_left()
{
    setPixmap(QPixmap(":/Character/Images/Characters/Link/arrow_left.png"));
    this->setPos(x()-50,y());
    arrow_life_timer++;

    if (arrow_life_timer == 6){
        QMediaPlayer *arrow_hit = new QMediaPlayer();
        arrow_hit->setMedia(QUrl("qrc:/arrow/Sounds/arrow_hit.mp3"));
        arrow_hit->play();
    }

    if(arrow_life_timer == 7)
        delete this;

}

void Arrow::move_right()
{
    setPixmap(QPixmap(":/Character/Images/Characters/Link/arrow_right.png"));
    this->setPos(x()+50,y());
    arrow_life_timer++;

    if (arrow_life_timer == 6){
        QMediaPlayer *arrow_hit = new QMediaPlayer();
        arrow_hit->setMedia(QUrl("qrc:/arrow/Sounds/arrow_hit.mp3"));
        arrow_hit->play();
    }

    if(arrow_life_timer == 7)
        delete this;
}

void Arrow::move_up()
{
    setPixmap(QPixmap(":/Character/Images/Characters/Link/arrow_up.png"));
    this->setPos(x(),y()-50);
    arrow_life_timer++;

    if (arrow_life_timer == 6){
        QMediaPlayer *arrow_hit = new QMediaPlayer();
        arrow_hit->setMedia(QUrl("qrc:/arrow/Sounds/arrow_hit.mp3"));
        arrow_hit->play();
    }

    if(arrow_life_timer == 7)
        delete this;
        //~Arrow();
}

void Arrow::move_down()
{
    setPixmap(QPixmap(":/Character/Images/Characters/Link/arrow_down.png"));
    this->setPos(x(),y()+50);
    arrow_life_timer++;

    if (arrow_life_timer == 6){
        QMediaPlayer *arrow_hit = new QMediaPlayer();
        arrow_hit->setMedia(QUrl("qrc:/arrow/Sounds/arrow_hit.mp3"));
        arrow_hit->play();
    }

    if(arrow_life_timer == 7)
        delete this;
}

//Arrow::~Arrow()
//{
//    delete this;
//}
