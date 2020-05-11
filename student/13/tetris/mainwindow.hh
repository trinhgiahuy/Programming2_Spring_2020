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

    // group of function control the Tetris block
        void newTetris();
        void getPosition();
        void showTetris();

private:
    Ui::MainWindow *ui;

    QGraphicsScene* Scene;

    QGraphicsScene* nextScene;

    QGraphicsScene* holdScene;


    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480; // 260; (in moving circle)
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240; // 680; (in moving circle)

    // Size of a Tetris component
    const int SQUARE_SIDE = 20;
    // Number of horizontal cells (places for Tetris components)
    const int COLUMNS = BORDER_RIGHT / SQUARE_SIDE;
    // Number of vertical cells (places for Tetris components)
    const int ROWS = BORDER_DOWN / SQUARE_SIDE;

    // Constants for different Tetriss and the number of them
        enum Tetris_kind {HORIZONTAL,
                             LEFT_CORNER,
                             RIGHT_CORNER,
                             SQUARE,
                             STEP_UP_RIGHT,
                             PYRAMID,
                             STEP_UP_LEFT,
                             NUMBER_OF_TetrisS};
        // From the enum values above, only the last one is needed in this template.
        // Recall from enum type that the value of the first enumerated value is 0,
        // the second is 1, and so on.
        // Therefore the value of the last one is 7 at the moment.
        // Remove those Tetris kinds above that you do not implement,
        // whereupon the value of NUMBER_OF_TetrisS changes, too.
        // You can also remove all the other values, if you do not need them,
        // but most probably you need a constant value for NUMBER_OF_TetrisS.


        // For randomly selecting the next dropping Tetris
        std::default_random_engine randomEng;
        std::uniform_int_distribution<int> distr;

        // More constants, attibutes, and methods
        // For tetronimo continuous moving
        QTimer timer_;

        // For calculate time of playing.
        QTimer gameRealTime;

        int bottomLimit;
        int leftLimit;
        int rightLimit;
        int upLimit;

        bool gameIsStarted = false;
        bool gameIsRunning = false;
        bool gameIsOver = false;

        Tetris currentTetris;
        Tetris nextTetris;
        Tetris holdTetris;

        bool canHold;
        bool isHoldEmpty;

        std::vector<Coord> HORIZONTAL_TETRIS = {Coord(0, 0), Coord(1, 0), Coord(2, 0), Coord(3, 0)};
        std::vector<Coord> LEFT_CORNER_TETRIS = {Coord(0, 0), Coord(0, 1), Coord(1, 1), Coord(2, 1)};
        std::vector<Coord> RIGHT_CORNER_TETRIS = {Coord(0, 1), Coord(1, 1), Coord(2, 1), Coord(2, 0)};
        std::vector<Coord> SQUARE_TETRIS = {Coord(0, 0), Coord(0, 1), Coord(1, 1), Coord(1, 0)};
        std::vector<Coord> STEP_UP_RIGHT_TETRIS = {Coord(0, 1), Coord(1, 1), Coord(1, 0), Coord(2, 0)};
        std::vector<Coord> PYRAMID_TETRIS = {Coord(0, 1), Coord(1, 1), Coord(1, 0), Coord(2, 1)};
        std::vector<Coord> STEP_UP_LEFT_TETRIS = {Coord(0, 0), Coord(1, 0), Coord(1, 1), Coord(2, 1)};


        std::vector<std::vector<Coord>> coordinateData = {HORIZONTAL_TETRIS,  LEFT_CORNER_TETRIS,RIGHT_CORNER_TETRIS
        ,SQUARE_TETRIS ,STEP_UP_RIGHT_TETRIS,PYRAMID_TETRIS,STEP_UP_LEFT_TETRIS};
         std::vector<QString> colorData = {{"#0444BF","#0584F2","#BE3B45","#55D9C0","#EDF259","#F07995"}};


        std::vector<int> bottomData = {0, 1, 1, 1, 1, 1, 1};
        std::vector<int> leftData = {0, 0, 0, 0, 0, 0, 0};
        std::vector<int> rightData = {3, 2, 2, 1, 2, 2, 2};
        std::vector<int> upData = {0, 0, 0, 0, 0, 0, 0};

        bool automaticMode;
        std::vector<std::vector<Square>> gameBoard;
        int playSpeed = 0;

        int min = 0;
        int sec = 0;
        int hour = 0;
};
#endif //MAINWINDOW_HH
