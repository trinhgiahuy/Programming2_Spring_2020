#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH
#include "tetrisblock.hh"
#include <QMainWindow>
#include <QGraphicsScene>
#include <random>
#include <QTimer>
#include <QGraphicsRectItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    //group of function display the window
    void setInitialWindow();
    void setInitialGame();
