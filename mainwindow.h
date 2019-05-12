#ifndef MAINWINDOW_H
#define MAINWINDOW_H


//#include <QMainWindow>
//#include <link.h>
//#include <QGraphicsScene>
//#include <scene.h>
//#include <controller.h>

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

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsScene *mapScene;   // scene ou carte
    Scene *cameraView;          // camera

    std::vector<QString> currentMap;
    std::map<QString, int> cellTypes;

    Controller *controller;

};

#endif // MAINWINDOW_H
