#ifndef TETRISBLOCK_HH
#define TETRISBLOCK_HH
#include <QGraphicsRectItem>
struct Coord
{
    int x = 0;
    int y = 0;

    Coord():
        x(0), y(0)
    {
    }

    Coord(int p_x, int p_y):
        x(p_x), y(p_y)
    {
    }
};

struct Square
{
    QGraphicsRectItem* block = NULL;
    Coord pos;
};

struct Tetris
{
    std::vector<Square> squares = std::vector<Square>(4, Square());
    int type = 0;
    QColor color = Qt::white;

    Tetris():
        squares(4, Square()),
        type(0),
        color(Qt::white)
    {
    }


};
#endif // TETRISBLOCK_HH
