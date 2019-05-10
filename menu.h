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

public slots:
    void openGameWindow();

private:
    Ui::menu *ui;
    QMediaPlayer menuMusic;
};

#endif // MENU_H
