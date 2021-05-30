#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QDebug>
#include <fstream>
#include <algorithm>
#include <cctype>

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
    
    void on_closePushButton_clicked();

    void on_findPushButton_clicked();


    void on_matchCheckBox_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HH
