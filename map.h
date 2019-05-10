#ifndef MAP_H
#define MAP_H

#include "scene.h"
#include "link.h"
#include "controller.h"
#include "ennemis.h"

//class Controller;

class Map:public QGraphicsView
{
public:
    Map();
    void setControl(Controller *controller) {
            this->controller = controller;
    }//ici on associe le controller à la vue
    void resetView();
    void initialiserScene();//on passe en paramètre le vecteur qui sera la carte

    void afficherPersonnage(Link *link);//methode pour mettre le personnage (pas top ici peut etre je sais pas
    void afficherEnnemis(Ennemis *ennemi);
    QGraphicsScene *getMapScene() const;
    Scene *getCameraView() const;

  protected:
    void keyPressEvent(QKeyEvent *event);
    void setMapScene(QGraphicsScene *value);
    void setCameraView(Scene *value);
    void affichageMenuEnHaut();

private:
    Controller *controller;//pour relier le controleur à la view
    QGraphicsScene *mapScene;//la map contient une scene:la carte
    Scene *cameraView;
    std::vector<QString> currentMap;
    std::map<QString, int> cellTypes;


};

#endif // MAP_H
