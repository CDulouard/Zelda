#include "scene.h"

Scene::Scene()
{
    this->posX = 0;
    this->posY = 0;
}

void Scene::setPosX(int i)
{
    this->posX = i;
}
void Scene::setPosY(int j)
{
    this->posY = j;
}
int Scene::getPosX()
{
    return this->posX;
}

int Scene::getPosY()
{
    return this->posY;
}
