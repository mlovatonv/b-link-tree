#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::ifstream infile("data.txt");
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
    const QString str = QString::fromStdString(tree.search(ui->searchText->toPlainText().toInt()));
    ui->resultText->setText(str);
    ui->searchText->setText("");
}
