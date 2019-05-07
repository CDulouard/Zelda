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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void display_map();
    void display_characters();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene = new QGraphicsScene();
};

#endif // MAINWINDOW_H
