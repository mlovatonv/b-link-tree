#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../b-link-tree/b-link-tree.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    BLinkTree<int, std::string> tree;
};

#endif // MAINWINDOW_H
