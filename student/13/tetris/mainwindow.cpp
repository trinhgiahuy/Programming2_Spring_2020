#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <fstream>
#include <utility>
#include <QColor>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), automaticMode(true)
{
    ui->setupUi(this);
    Scene = new QGraphicsScene(this);
    nextScene = new QGraphicsScene(this);
    holdScene = new QGraphicsScene(this);

    timer_.setSingleShot(false);
    gameRealTime.setSingleShot(false);

    connect(&timer_, &QTimer::timeout, this, &MainWindow::automaticDrop);
    connect(&gameRealTime, &QTimer::timeout, this, &MainWindow::playingTime);

    connect(ui->pausePushButton, &QPushButton::clicked, this, &MainWindow::pauseGame);

    // Setting random engine ready for the first real call.
    int seed = time(0); // You can change seed value for testing purposes
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TetrisS - 1);
    distr(randomEng); // Wiping out the first random number (which is almost always 0)
    // After the above settings, you can use randomEng to draw the next falling
    // Tetris by calling: distr(randomEng) in a suitable method.

    // Add more initial settings and connect calls, when needed.
    setInitialWindow();
    setInitialGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setInitialWindow()
{
    // The graphicsView object is placed on the window
    // at the following coordinates, but if you want
    // different placement, you can change their values.
    int left_margin = 100; // x coordinate
    int top_margin = 150; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(left_margin, top_margin,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(Scene);
    // The width of the Scene is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a Tetris is considered to be inside the SceneRect,
    // if its upper left corner is inside the SceneRect.
    Scene->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    nextScene->setSceneRect(0, 0, 114 - 1, 60 -1);

    holdScene->setSceneRect(0, 0, 60 - 1, 60- 1);

}
/**
 * @brief Set initial information for the game
 */
void MainWindow::setInitialGame()
{
    Scene->clear();
    nextScene->clear();
    holdScene->clear();

    currentTetris = Tetris();
    nextTetris  = Tetris();
    holdTetris = Tetris();
    gameBoard = std::vector<std::vector<Square>>(ROWS, std::vector<Square>(COLUMNS, Square()));

    leftLimit = 0;
    rightLimit = 0;
    upLimit = 0;
    bottomLimit = 0;
    currentTetris.color = nextTetris.color;

    // Time related information in the game.
    min = 0;
    sec = 0;
    hour = 0;
    ui->lcdMin->display(0);
    ui->lcdSec->display(0);
    playSpeed = 800;
    ui->startButton->setEnabled(true);

    //set initial condition
    gameIsStarted = false;
    gameIsOver = false;
    gameIsRunning = false;
    canHold = true;
    isHoldEmpty = true;
    holdTetris.type = 0;
    nextTetris.type = distr(randomEng) % 7;
    int colorIndex = distr(randomEng) % 5;
    nextTetris.color = colorData.at(colorIndex);
}

