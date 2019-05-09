#include "link.h"
#include "arrow.h"
#include "mainwindow.h"

#include<QKeyEvent>
#include<QGraphicsScene>
#include<QDebug>


using namespace std;

extern QString lastMove;
extern map<QString, int> cellTypes;
QString lastMove = "right";

Link::Link()
{
    setPixmap(QPixmap(":/Character/Images/Characters/Link/link_down.png"));
    setPos(50,50);
    this->m_health = 100;
    this->m_power = 100;
    this->_arrowQuantity = 5;
    this->_arrowDamages = 25;
    this->_swordDamages = 50;
}


void Link::keyPressEvent(QKeyEvent *event)
{
    // Movements
    if ((event->key() == Qt::Key_Left) || (event->key() == Qt::Key_A))
        move_left();

    else if ((event->key() == Qt::Key_Right) || (event->key() == Qt::Key_D))
        move_right();

    else if ((event->key() == Qt::Key_Up) || (event->key() == Qt::Key_W))
        move_up();

    else if ((event->key() == Qt::Key_Down) || (event->key() == Qt::Key_S))
        move_down();

    // Attaque normal
    else if (event->key() == Qt::Key_H)
        basic_assault();

    // Attaque puissante (circulaire, consomme energie)
    else if (event->key() == Qt::Key_J)
        strong_assault();

    // Tirer une flèche
    else if ((event->key() == Qt::Key_K) || (event->key() == Qt::Key_Space))
        shoot();

}

void Link::move_left()
{
    this->setPixmap(QPixmap(":/Character/Images/Characters/Link/link_left.png"));
    if(this->x()-50 >= 0){
        setPos(x()-50,y());
        lastMove = "left";
        qDebug() << this->pos();
    }
}

void Link::move_right()
{
    this->setPixmap(QPixmap(":/Character/Images/Characters/Link/link_right.png"));
    if(this->x()+50 < 1000){
        this->setPos(x()+50,y());
        lastMove = "right";
        qDebug() << this->pos();
    }
}

void Link::move_up()
{
    this->setPixmap(QPixmap(":/Character/Images/Characters/Link/link_up.png"));
    if(this->y()-50 >=0){
        this->setPos(x(),y()-50);
        lastMove = "up";
        qDebug() << this->pos();
    }
}

void Link::move_down()
{
    this->setPixmap(QPixmap(":/Character/Images/Characters/Link/link_down.png"));
    if(this->y()+50 <= 600){
        this->setPos(x(),y()+50);
        lastMove = "down";
        qDebug() << this->pos();
    }
}

void Link::basic_assault()
{
}

void Link::strong_assault()
{
}

void Link::shoot()
{
    if (_arrowQuantity > 0){
        Arrow *arrow = new Arrow();
        arrow->setPos(x(),y());
        scene()->addItem(arrow);

        //we remove an arrow
        //_arrowQuantity = ui->Arrows_display->intValue();
        //_arrowQuantity--;
        //emit_change_arrow_quantity(_arrowQuantity--);
        //connect(this, SIGNAL(emit_change_arrow_quantity()), MainWindow, SLOT(move_left()));


    }
}

//void Link::emit_change_health()
//{
//    emit change_health();
//}

//void Link::emit_change_power()
//{
//    emit change_power();
//}

//void Link::emit_change_arrow_quantity()
//{
//    emit change_arrow_quantity();
//}


