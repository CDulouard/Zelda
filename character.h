#ifndef CHARACTER_H
#define CHARACTER_H

//#include <vector>
//#include <map>
//#include <string>
#include <QGraphicsPixmapItem>

class Character:public QGraphicsPixmapItem {
public:
    Character();
    void setPosX(int i);
    void setPosY(int j);
    void setLife(int life);
    int getPosX();
    int getPosY();
    float getLife();
    QPixmap getTile();

//    void Move(char x, char y, std::vector<std::string> *map, std::map<std::string, int> cellTypes);
//    void move_left();
//    void move_right();
//    void move_up();
//    void move_down();
//    void basic_assault();

protected:
    int posX;//position sur la carte
    int posY;//
    float life;//vie du personnage qui doit etre > ou = à 0

    QPixmap tile;
    float m_health;
    float m_energy;
    float m_power; /*  amount of damages the character deals  */
    double m_range;  /*  max distance of a a hit */   // inutile je pense
    float m_speed;





};

#endif // CHARACTER_H
