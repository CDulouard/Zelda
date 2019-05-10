#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>

extern std::vector<QString> currentMap;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}
