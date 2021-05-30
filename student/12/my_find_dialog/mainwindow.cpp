#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_closePushButton_clicked()
{
    this->close();
}


void MainWindow::on_findPushButton_clicked()
{

}

void MainWindow::on_matchCheckBox_clicked()
{
    sign = ui->matchCheckBox->isChecked();
}
