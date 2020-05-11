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

/**
 * @brief A function control the input from the keyboard
 * @param event
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_A)
    {
        if (canMoveLeft())
        {
           // Move to the left one square.
           moveLeft();
        }

        return;
    }

    if (event->key() == Qt::Key_D)
    {
        if (canMoveRight())
        {
            // Move to the right one square.
            moveRight();
        }
        return;
    }

    if (event->key() == Qt::Key_W)
    {
        // Rotation
        rotate();
        return;
    }

}

/**
 * @brief A function will create a new Tetris block
 */
void MainWindow::newTetris()
{
    // Getting information to make new Tetris.
    currentTetris.type = nextTetris.type;
    currentTetris.color = nextTetris.color;


    for (int i = 0; i < 4; ++i)
    {
        currentTetris.squares.at(i).pos.x = coordinateData.at(currentTetris.type).at(i).x;
        currentTetris.squares.at(i).pos.y = coordinateData.at(currentTetris.type).at(i).y;

        bottomLimit = bottomData.at(currentTetris.type);
        leftLimit = leftData.at(currentTetris.type);
        rightLimit = rightData.at(currentTetris.type);
        upLimit = upData.at(currentTetris.type);
    }

    // Set appearance position of new Tetris.
    getPosition();

    // Prepare information of the next Tetris.
    nextTetris.type = distr(randomEng) % 7;
    int colorIndex = distr(randomEng) % 5;
    nextTetris.color = colorData.at(colorIndex);
}

/**
 * @brief A function return a postion of
 * the Tetris block
 */

void MainWindow::getPosition()
{
    // Make appearing option.

    int deltaX = ((COLUMNS - 1) / 2) - (rightLimit - leftLimit) / 2;
    for (int i = 0; i < 4; ++i)
    {
        currentTetris.squares.at(i).pos.x += deltaX;
    }

    leftLimit += deltaX;
    rightLimit += deltaX;
}
/**
 * @brief A function show the Tetris block
 */
void MainWindow::showTetris()
{
    if (!gameIsOver)
    {
        // Choosing color for new Tetris from the color of this level.

        for (int i = 0; i < 4; ++i)
        {
            Coord alterCoordinate(currentTetris.squares.at(i).pos);
            currentTetris.squares.at(i).block = Scene->addRect(0, 0, SQUARE_SIDE,
                                                                  SQUARE_SIDE, QPen(Qt::black),
                                                                  QBrush(currentTetris.color));

            currentTetris.squares.at(i).block->setPos(alterCoordinate.x * SQUARE_SIDE,
                                                        alterCoordinate.y * SQUARE_SIDE);
        }
    }
    else
    {
        int moveUp = 1;
        while (bottomLimit - moveUp >= 0)
        {
            bool found_suitable_position = true;
            for (int i = 0; i < 4; ++i)
            {
                Coord alterCoordinate(currentTetris.squares.at(i).pos);
                alterCoordinate.y -= moveUp;

                // Check only part apper on the Scene.
                if (alterCoordinate.y >= 0)
                {
                    if (gameBoard.at(alterCoordinate.y).at(alterCoordinate.x).block!= NULL)
                    {
                        found_suitable_position = false;
                        break;
                    }
                }
            }

            if (found_suitable_position)
            {
                break;
            }

            // Try moving up one unit.
            moveUp += 1;
        }

        if (bottomLimit - moveUp >= 0)
        {
            for (int i = 0; i < 4; ++i)
            {
                Coord alterCoordinate(currentTetris.squares.at(i).pos);

                alterCoordinate.y -= moveUp;

                if (alterCoordinate.y >= 0)
                {
                    gameBoard.at(alterCoordinate.y).at(alterCoordinate.x).block= Scene->addRect(0, 0,SQUARE_SIDE,
                                        SQUARE_SIDE, QPen(), QBrush(currentTetris.squares.at(i).block->brush()));

                    gameBoard.at(alterCoordinate.y).at(alterCoordinate.x).block->setPos(alterCoordinate.x * SQUARE_SIDE,
                                                                                        alterCoordinate.y * SQUARE_SIDE);
                }
            }
        }
    }
}



