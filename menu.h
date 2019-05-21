#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include<QMediaPlayer>

namespace Ui {
class menu;
}

class menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::menu *ui;
};

#endif // MENU_H
