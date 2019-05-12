#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : QGraphicsScene
{
public:
    Scene();
    void setPosX(int i);
    void setPosY(int j);
    int getPosX();
    int getPosY();

private:
    int posX;
    int posY;
};

#endif // SCENE_H
