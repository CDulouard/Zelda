#include "link.h"
#include "arrow.h"

#include<QKeyEvent>
#include<QDebug>
#include<QGraphicsScene>


using namespace std;

extern QString lastMove;
extern map<QString, int> cellTypes;

Link::Link()
{
    //ui->SanteValeur->display(100);
}


void Link::keyPressEvent(QKeyEvent *event)
{
    // Movements

    if ((event->key() == Qt::Key_Left) || (event->key() == Qt::Key_A)){
        if(this->x()-50 >= 0){
            this->setPixmap(QPixmap(":/Character/Images/Characters/Link/link_left.png"));
            setPos(x()-50,y());
            lastMove = "left";
            qDebug() << this->pos();
        }
    }

    if ((event->key() == Qt::Key_Right) || (event->key() == Qt::Key_D)){
        if(this->x()+50 < 1000){
            this->setPixmap(QPixmap(":/Character/Images/Characters/Link/link_right.png"));
            this->setPos(x()+50,y());
            lastMove = "right";
            qDebug() << this->pos();
        }
    }

    if ((event->key() == Qt::Key_Up) || (event->key() == Qt::Key_W)){
        if(this->y()-50 >=0){
            this->setPos(x(),y()-50);
            lastMove = "up";
            qDebug() << this->pos();
        }
    }

    if ((event->key() == Qt::Key_Down) || (event->key() == Qt::Key_S)){
        if(this->y()+50 <= 600){
            this->setPos(x(),y()+50);
            lastMove = "down";
            qDebug() << this->pos();
        }
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


