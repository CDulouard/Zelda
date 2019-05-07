#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <map>
#include <string>
#include <QGraphicsPixmapItem>

class Character:public QGraphicsPixmapItem {
public:
    void Move(char x, char y, std::vector<std::string> *map, std::map<std::string, int> cellTypes);

protected:
    float m_posx;   // existe déjà dans la classe parente
    float m_posy;   // existe déjà dans la classe parente
    float m_size;   /*  size of the character   */
    float m_speed;
    int m_health;
    int m_power;    /*  amount of damages the character deals  */
    float m_range;  /*  max distance of a a hit */
};

#endif // CHARACTER_H