#ifndef MODEL_H
#define MODEL_H

class Model
{
public:
    Model();

    class Link *getLink() const;
    void setLink(Link *value);

    class Zelda *getZelda() const;
    void setZelda(Zelda *value);

    void resetModel();

private:
    Link *link;
    Zelda *zelda;

};

#endif // MODEL_H
