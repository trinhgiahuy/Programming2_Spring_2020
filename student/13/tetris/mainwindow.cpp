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
/**
 * @brief A function will automatic create new
 * Tetris block
 */
void MainWindow::automaticDrop()
{
    if (canMoveDown())
    {
        moveDown();
    }
    else
    {
        timer_.stop();
        updateGame();
    }
}

/**
 * @brief Function control Tetris block to move leftward
 */
void MainWindow::moveLeft()
{
    for (int i = 0; i < 4; ++i)
    {
        currentTetris.squares.at(i).block->moveBy(-SQUARE_SIDE, 0);
        --currentTetris.squares.at(i).pos.x;
    }

    --leftLimit;
    --rightLimit;
}

/**
 * @brief Function control Tetris block to move rightward
 */
void MainWindow::moveRight()
{
    for (int i = 0; i < 4; ++i)
    {
        currentTetris.squares.at(i).block->moveBy(SQUARE_SIDE, 0);
        ++currentTetris.squares.at(i).pos.x;
    }

    ++leftLimit;
    ++rightLimit;
}

/**
 * @brief Function control Tetris block to move downward
 */
void MainWindow::moveDown()
{
    for (unsigned int i = 0; i < 4; ++i)
    {
       currentTetris.squares.at(i).block->moveBy(0, SQUARE_SIDE);
       ++currentTetris.squares.at(i).pos.y;
    }

    ++bottomLimit;
    ++upLimit;

}

/**
 * @brief The function check if the block can rotate
 * @return true if it can or false otherwise
 */
bool MainWindow::rotation_calculation()
{
    std::vector<Coord> rotation_result;
    std::vector<std::pair<double, double>> coord_conversion;
    std::pair<double, double> rotation_center = std::make_pair(0, 0);

    // Convert coordinates to real number.
    for (int i = 0; i < 4; ++i)
    {
        Coord alterCoordinate(currentTetris.squares.at(i).pos);
        coord_conversion.push_back(std::make_pair(alterCoordinate.x + 0.5, alterCoordinate.y + 0.5));
        rotation_center.first += coord_conversion.at(i).first;
        rotation_center.second += coord_conversion.at(i).second;
    }

    rotation_center.first /= 4;
    rotation_center.second /= 4;

    //  Convert coordinate back to integer.
    for (int i = 0; i < 4; ++i)
    {
        Coord alterCoordinate;
        alterCoordinate.x = ceil(rotation_center.first +
            (coord_conversion.at(i).second - rotation_center.second)) - 1;

        alterCoordinate.y = ceil(rotation_center.second -
            (coord_conversion.at(i).first - rotation_center.first)) - 1;

        rotation_result.push_back(alterCoordinate);
    }

    bool can_rotate = true;
    for (int i = 0; i < 4; ++i)
    {
        Coord alterCoordinate(rotation_result.at(i));

        // Check the outermost left limit
        if (alterCoordinate.x < 0)
        {
            can_rotate = false;
            break;
        }

        // Check the outermost right limit
        if (alterCoordinate.x >= COLUMNS)
        {
            can_rotate = false;
            break;
        }

        // Check the outermost downward limit
        if (alterCoordinate.y < 0)
        {
            can_rotate = false;
            break;
        }

        // Check the outermost upward limit
        if (alterCoordinate.y >= ROWS)
        {
            can_rotate = false;
            break;
        }

        // There there is other Tetris.
        if (gameBoard.at(alterCoordinate.y).at(alterCoordinate.x).block!= NULL)
        {
            can_rotate = false;
            break;
        }
    }

    if (can_rotate)
    {
        for (int i = 0; i < 4; ++i)
        {
            currentTetris.squares.at(i).pos.x = rotation_result.at(i).x;
            currentTetris.squares.at(i).pos.y = rotation_result.at(i).y;
        }
    }

    return can_rotate;
}

/**
 * @brief The function rotate the Retris counter clock wise
 */
void MainWindow::rotate()
{

    if (!rotation_calculation())
    {
        return;
    }

    int new_bottom = -1;
    int new_up = ROWS;
    int new_left = COLUMNS;
    int new_right = -1;

    for (int i = 0; i < 4; ++i)
    {
        if (currentTetris.squares.at(i).pos.y < new_up)
        {
            new_up = currentTetris.squares.at(i).pos.y;
        }

        if (currentTetris.squares.at(i).pos.y > new_bottom)
        {
            new_bottom = currentTetris.squares.at(i).pos.y;
        }

        if (currentTetris.squares.at(i).pos.x < new_left)
        {
            new_left = currentTetris.squares.at(i).pos.x;
        }

        if (currentTetris.squares.at(i).pos.x > new_right)
        {
            new_right = currentTetris.squares.at(i).pos.x;
        }

        currentTetris.squares.at(i).block->setPos(currentTetris.squares.at(i).pos.x * SQUARE_SIDE,
                                                    currentTetris.squares.at(i).pos.y * SQUARE_SIDE);
    }

    // Update the Tetris
    bottomLimit = new_bottom;
    upLimit = new_up;
    rightLimit = new_right;
    leftLimit = new_left;
}

/**
 * @brief The function check that whether the Tetris block can move down
 * or not
 * @return true if it can or false otherwise
 */
bool MainWindow::canMoveDown()
{
    //Check that the Tetris cannot be move down
    if (bottomLimit + 1 >= ROWS)
    {
        return false;
    }

    for (int i = 0; i < 4; ++i)
    {
        Coord alterCoordinate(currentTetris.squares.at(i).pos);

        if (gameBoard.at(alterCoordinate.y + 1).at(alterCoordinate.x).block!= NULL)
        {
            return false;
        }
    }

    //Else it can still move downward
    return true;
}

/**
 * @brief The function check that whether the Tetris block can move left
 * or not
 * @return true if it can and false otherwise
 */
bool MainWindow::canMoveLeft()
{
    // Check the outermost left limit
    if (leftLimit - 1 < 0)
    {
        return false;
    }

    // There are other Tetriss on the left.
    for (int i = 0; i < 4; ++i)
    {
        int x_index = currentTetris.squares.at(i).pos.x;
        int y_index = currentTetris.squares.at(i).pos.y;

        if (gameBoard.at(y_index).at(x_index - 1).block!= NULL)
        {
            return false;
        }
    }

    // The Tetris can move to the left.
    return true;
}

/**
 * @brief The function check that whether the Tetris block can move right
 * or not
 * @return true if it can and false otherwise
 */
bool MainWindow::canMoveRight()
{
    //  Check the outermost right limit
    if (rightLimit + 1 >= COLUMNS)
    {
        return false;
    }

    // There are other Tetriss on the right.
    for (int i = 0; i < 4; ++i)
    {
        int x_index = currentTetris.squares.at(i).pos.x;
        int y_index = currentTetris.squares.at(i).pos.y;

        if (gameBoard.at(y_index).at(x_index + 1).block!= NULL)
        {
            return false;
        }
    }

    // The Tetris can move to the left
    return true;
}
/**
 * @brief A function that will draw Next Tetris
 */
void MainWindow::drawNextTetris()
{
    nextScene->clear();

    for (int i = 0; i < 4; ++i)
    {
        nextTetris.squares.at(i).pos.x = coordinateData.at(nextTetris.type).at(i).x;
        nextTetris.squares.at(i).pos.y = coordinateData.at(nextTetris.type).at(i).y;

        nextTetris.squares.at(i).block = nextScene->addRect(0, 0, SQUARE_SIDE / 1.2,
                                SQUARE_SIDE / 1.2,QPen(), QBrush(nextTetris.color));
        Coord alterCoordinate(nextTetris.squares.at(i).pos);
        nextTetris.squares.at(i).block->setPos(alterCoordinate.x * SQUARE_SIDE + 30,
                                               alterCoordinate.y * SQUARE_SIDE + 10);
    }

}




