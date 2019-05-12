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

    int getLevelCounter() const;
    void setLevelCounter(int newCounter);

    int getPlayButtonPressedOrNot() const;
    void setPlayButtonPressedOrNot(int newValue);

public slots:
    int playButtonPressed();

protected:
    Ui::menu *ui;
    QMediaPlayer menuMusic;
    int playButtonPressedOrNot;
};

#endif // MENU_H
