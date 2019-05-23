#include "model.h"
#include "link.h"
#include "zelda.h"

Model::Model()
{
    this->link = new Link();
    this->zelda = new Zelda();
}

Link *Model::getLink() const
{
    return link;
}

void Model::setLink(Link *value)
{
    link = value;
}

Zelda *Model::getZelda() const
{
    return zelda;
}

void Model::setZelda(Zelda *value)
{
    zelda = value;
}

void Model::resetModel()
{
    this->link = new Link();
    this->zelda = new Zelda();
}
