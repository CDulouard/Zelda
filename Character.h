#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <map>
#include <string>

class Character {
public:
    void Move(char x, char y, std::vector<std::string> *map, std::map<std::string, int> cellTypes);

private:
    float m_posx;
    float m_posy;
    float m_size;   /*  size of the character   */
    float m_speed;
    int m_health;
    int m_power;    /*  amount of damages the character deals  */
    float m_range;  /*  max distance of a a hit */
};

#endif // CHARACTER_H
