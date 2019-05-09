#include "headers.h"

#include<QKeyEvent>
#include<QGraphicsScene>
#include<QDebug>


using namespace std;


extern map<QString, int> cellTypes;
QString lastMove = "right";

Link::Link()
{
    setPixmap(QPixmap(":/Character/Images/Characters/Link/link_down.png"));
    setPos(50,50);
    this->m_health = 100;
    this->m_speed = 1;
    this->m_range = 1;
    this->m_energy = 100;
    this->_arrowQuantity = 5;
    this->_arrowDamages = 25;
    this->_swordDamages = 50;
}


void Link::keyPressEvent(QKeyEvent *event)
{
    // Movements
    if ((event->key() == Qt::Key_Left) || (event->key() == Qt::Key_A)){
        this->setPixmap(QPixmap(":/Character/Images/Characters/Link/link_left.png"));
        move_left();
        lastMove = "left";
        qDebug() << this->pos();
    }

    else if ((event->key() == Qt::Key_Right) || (event->key() == Qt::Key_D)){
        this->setPixmap(QPixmap(":/Character/Images/Characters/Link/link_right.png"));
        move_right();
        lastMove = "right";
        qDebug() << this->pos();
    }

    else if ((event->key() == Qt::Key_Up) || (event->key() == Qt::Key_W)){
        this->setPixmap(QPixmap(":/Character/Images/Characters/Link/link_up.png"));
        move_up();
        lastMove = "up";
        qDebug() << this->pos();
    }

    else if ((event->key() == Qt::Key_Down) || (event->key() == Qt::Key_S)){
        this->setPixmap(QPixmap(":/Character/Images/Characters/Link/link_down.png"));
        move_down();
        lastMove = "down";
        qDebug() << this->pos();
    }

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


