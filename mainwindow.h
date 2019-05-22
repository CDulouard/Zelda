#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMediaPlayer>

#include <QMainWindow>
#include <link.h>
#include <scene.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resetView();

    void displayMap();
    void displayLink(Link *link);
    void displayEnnemis(class Ennemis *ennemi);
    void displayZelda(class Zelda *Zelda);

    void displayStats(int health, int arrowNmber, int energy);

    void keyPressEvent(QKeyEvent *event);

    QGraphicsScene *getMapScene() const;

    Scene *getCameraView() const;
    void setCameraView(Scene *value);

    std::vector<Ennemis*> getEnnemisList() const;
    void setEnnemisList(const std::vector<Ennemis*> &value);

    void ajouterItem(int posX,int posY, QString s);

    std::vector<QString> currentMap;

protected:
    Ui::MainWindow *ui;

    QGraphicsScene *mapScene;   // scene ou carte
    Scene *cameraView;          // camera

    std::map<QString, int> cellTypes;

    std::vector<Ennemis*> ennemisList;
    Zelda *princessZelda;

    std::vector<class Item *> mapItems;


};

#endif // MAINWINDOW_H
