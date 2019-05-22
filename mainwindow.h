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

    void keyPressEvent(QKeyEvent *event);

    Scene *getCameraView() const;
    void setCameraView(Scene *value);

    std::vector<class Ennemis*> getMonstres() const;
    void setMonstres(const std::vector<Ennemis*> &value);

    void displayEnnemis(Ennemis *ennemi);

    std::vector<QString> currentMap;

protected:
    Ui::MainWindow *ui;
    QGraphicsScene *mapScene;   // scene ou carte
    Scene *cameraView;          // camera
    std::map<QString, int> cellTypes;
    std::vector<Ennemis*> monstres;


};

#endif // MAINWINDOW_H
