#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void display_map();
    void display_characters();

    ~MainWindow();

//public slots:
//    void change_health();
//    void change_power();
//    void change_arrow_quantity();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene = new QGraphicsScene();

};

#endif // MAINWINDOW_H
