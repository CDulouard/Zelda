#ifndef MODEL_H
#define MODEL_H

#include <link.h>

class Model
{
public:
    Model();

    Link *getLink() const;
    void setLink(Link *value);

    void resetModel();

//    Niveaux *getNiveau() const;
//    void setNiveau(Niveaux *value);


private:
    Link *link;
//    Niveaux *niveau;

};

#endif // MODEL_H
