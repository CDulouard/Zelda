#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
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
    void initialiserScene();

    void display_map();
    void display_characters();


//public slots:
//    void change_health();
//    void change_power();
//    void change_arrow_quantity();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsScene *mapScene;//la map contient une scene:la carte
    Scene *cameraView;

    std::vector<QString> currentMap;
    std::map<QString, int> cellTypes;

};

#endif // MAINWINDOW_H
