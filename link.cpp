#include "link.h"

Link::Link()
{
    this->setPosX(0);
    this->setPosY(0);
    this->setLife(8);//on met une vie de 5 coeurs
    this->number = 1;//pour les tiles et l'animastion
    this->direction = "down";//pour connaitre si il regarde a gauche ou a droite
    this->tile = QPixmap("/Users/alexandremagne/Desktop/Zelda2/Tiles/link_down/10.png").scaled(30,30);//image par défaut
    this->isAmoradoOrNot = 0;
    this->LoadingCircularAttack = 250;//pour avoir les 10 sec
}

int Link::arrowCounter()
{
    return _arrowQuantity;
}


int Link::getNumber() const
{
    return number;
}

void Link::setNumber(int value)
{
    number = value;
}
QString Link::getDirection() const
{
    return direction;
}

void Link::setDirection(const QString &value)
{
    direction = value;
}

int Link::getSpeed() const
{
    return speed;
}

void Link::setSpeed(int value)
{
    speed = value;
}

int Link::getLoadingCircularAttack() const
{
    return LoadingCircularAttack;
}

void Link::setLoadingCircularAttack(int value)
{
    LoadingCircularAttack = value;
}

int Link::getIsAmoradoOrNot() const
{
    return isAmoradoOrNot;
}

void Link::setIsAmoradoOrNot(int value)
{
    isAmoradoOrNot = value;
}



//#include "link.h"
//#include "arrow.h"

//#include<QKeyEvent>
//#include<QGraphicsScene>
//#include<QDebug>


//using namespace std;

////QString lastMove = "right";
//extern map<QString, int> cellTypes;


//Link::Link()
//{
//    this->tile = (QPixmap(":/Character/Images/Characters/Link/link_down.png"));
//    this->setPos(50,50);
//    this->setFlag(QGraphicsItem::ItemIsFocusable); // A bouger dans le mainWindow
//    this->setFocus();                               // pour eviter le bug de perte de link

//    this->m_health = 100;
//    this->m_speed = 1;
//    this->m_range = 1;
//    this->m_energy = 100;
//}

//QString Link::getlastMove()
//{
//    return _lastMove;
//}

//void Link::setlastMove(QString lastMove)
//{
//    this->_lastMove = lastMove;
//}




//void Link::keyPressEvent(QKeyEvent *event)
//{
//    // Movements
//    if ((event->key() == Qt::Key_Left) || (event->key() == Qt::Key_A)){
//        this->setPixmap(QPixmap(":/Character/Images/Characters/Link/link_left.png"));
//        move_left();
//        set_lastMove("left");
//        //lastMove = "left";
//        qDebug() << this->pos();
//    }

//    else if ((event->key() == Qt::Key_Right) || (event->key() == Qt::Key_D)){
//        this->setPixmap(QPixmap(":/Character/Images/Characters/Link/link_right.png"));
//        move_right();
//        set_lastMove("right");
//        //lastMove = "right";
//        qDebug() << this->pos();
//    }

//    else if ((event->key() == Qt::Key_Up) || (event->key() == Qt::Key_W)){
//        this->setPixmap(QPixmap(":/Character/Images/Characters/Link/link_up.png"));
//        move_up();
//        set_lastMove("up");
//        //lastMove = "up";
//        qDebug() << this->pos();
//    }

//    else if ((event->key() == Qt::Key_Down) || (event->key() == Qt::Key_S)){
//        this->setPixmap(QPixmap(":/Character/Images/Characters/Link/link_down.png"));
//        move_down();
//        set_lastMove("down");
//        //lastMove = "down";
//        qDebug() << this->pos();
//    }

//    // Attaque normal
//    else if (event->key() == Qt::Key_H)
//        basic_assault();

//    // Attaque puissante (circulaire, consomme energie)
//    else if (event->key() == Qt::Key_J)
//        strong_assault();

//    // Tirer une flèche
//    else if ((event->key() == Qt::Key_K) || (event->key() == Qt::Key_Space))
//        shoot();

//}



//void Link::strong_assault()
//{
//}

//void Link::shoot()
//{
//    if (_arrowQuantity > 0){
//        Arrow *arrow = new Arrow(_lastMove);
//        arrow->setPos(x(),y());
//        scene()->addItem(arrow);

//        //we remove an arrow
//        //_arrowQuantity--;
//        //emit_change_arrow_quantity(_arrowQuantity--);
//        //connect(this, SIGNAL(emit_change_arrow_quantity()), MainWindow, SLOT(move_left()));

//    }
//}

