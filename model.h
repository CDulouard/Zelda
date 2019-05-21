#ifndef MODEL_H
#define MODEL_H

class Model
{
public:
    Model();

    class Link *getLink() const;
    void setLink(Link *value);

    void resetModel();

private:
    Link *link;

};

#endif // MODEL_H
