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
    void displayZelda(class Zelda *zelda);
    void displayEnnemis(class Ennemis *ennemi);

    void displayStats(int health, int arrowNmber, int energy);

    void keyPressEvent(QKeyEvent *event);

    QGraphicsScene *getMapScene() const;

    Scene *getCameraView() const;
    void setCameraView(Scene *value);

    std::vector<QString> getCurrentMap();

    std::map<QString, int> getCellTypes();

    std::vector<Ennemis*> getEnnemisList() const;
    void setEnnemisList(const std::vector<Ennemis*> &value);

    void ajouterItem(int posX,int posY, QString s);

    void deleteMonster(int nbMonster);

    void displayMapItems( std::vector<class Item*> vec);
    std::vector<Item *> getMapItems() const;

protected:
    Ui::MainWindow *ui;

    QGraphicsScene *mapScene;   // scene ou carte
    Scene *cameraView;          // camera

    std::map<QString, int> cellTypes;

    std::vector<Ennemis*> ennemisList;
    Zelda *princessZelda;

    std::vector<class Item *> mapItems;

    std::vector<QString> currentMap;

};

#endif // MAINWINDOW_H
