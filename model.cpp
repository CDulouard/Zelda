#include "model.h"
#include "link.h"
Model::Model()
{
    this->link = new Link();
}

Link *Model::getLink() const
{
    return link;
}

void Model::setLink(Link *value)
{
    link = value;
}

void Model::resetModel(){
    this->link = new Link();
}



