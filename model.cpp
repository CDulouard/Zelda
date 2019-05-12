#include "game.h"

Model::Model()
{
    this->link = new Link();
//    this->niveau = new Niveaux();


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
//    this->niveau = new Niveaux();
}


//Niveaux *Model::getNiveau() const
//{
//    return niveau;
//}

//void Model::setNiveau(Niveaux *value)
//{
//    niveau = value;
//}



