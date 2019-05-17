#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const std::string path = "/home/mlovatonv/utec/ada/b-link-tree/b-link-tree-gui/data.txt";
    std::ifstream infile(path);
    std::string line;
    int key;
    std::string data;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        if (!(iss >> key >> data)) { break; } // error
        tree.insert(key, data);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    const QString str = QString::fromStdString(tree.search(ui->searchText->toPlainText().toInt(), "No se encontró."));
    ui->resultText->setText(str);
    ui->searchText->setText("");
}
