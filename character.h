#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <map>
#include <string>
#include <QGraphicsPixmapItem>

class Character:public QGraphicsPixmapItem {
public:
    void Move(char x, char y, std::vector<std::string> *map, std::map<std::string, int> cellTypes);
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    void basic_assault();

    float get_m_health();
    void set_m_health(float health);

protected:
    //double m_posx;   // existe déjà dans la classe parente, fonction x()
    //double m_posy;   // existe déjà dans la classe parente, fonction y()
    //double m_size;   /*  size of the character   */ je suis parti sur une taille standard de 50x50


    float m_health;
    float m_energy;
    float m_power; /*  amount of damages the character deals  */
    double m_range;  /*  max distance of a a hit */   // inutile je pense
    float m_speed;
};

#endif // CHARACTER_H
