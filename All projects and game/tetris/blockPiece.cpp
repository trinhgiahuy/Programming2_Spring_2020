#include <QDebug>
#include <QKeyEvent>


//void Block::keyPressEvent(QKeyEvent *event)
//{
//    qDebug() <<"OK";
//    if(event->key() == Qt::Key_Left ){
//        setPos(x()-20,y());
//    }else if (event->key()== Qt::Key_Right){
//        setPos(x()+20,y());
//    }else if (event->key() == Qt::Key_Down){
//        setPos(x(),y()+20);
//    }
//}

void BlockPiece::getRandomShape()
{

}

void BlockPiece::getShape(BlockShape shape)
{
    static constexpr int coordTable[8][4][2] = {
{ { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
{ { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
{ { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
{ { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
{ { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
{ { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
{ { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
{ { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }
};

    for (int i = 0; i<4; i++){
        for (int j = 0; j<2; j++){
            coord[i][j] = coordTable[shape][i][j];
        }
    }
    blockShape = shape;
}

int BlockPiece::getMinX() const
{
    int min = coord[0][0];
    for (int i = 1; i < 4; ++i)
        min = qMin(min, coord[i][0]);
    return min;
}

int BlockPiece::getMaxX() const
{
    int max = coord[0][0];
    for(int i=1; i<4; i++){
        max = qMax(max, coord[i][0]);
    }
    return max;
}

int BlockPiece::getMinY() const
{
    int min = coord[0][1];
    for (int j = 1; j < 4; j++)
        min = qMin(min, coords[j][1]);
    return min;
}

int BlockPiece::getMaxY() const
{
    int max = coord[0][1];
    for (int j = 1; j < 4; j++)
        max = qMax(min, coords[j][1]);
    return max;
}

/**
 * @brief a function turn a block anti-clockwise direction
 * @return a class BlockPiece
 */
BlockPiece BlockPiece::anti_clockwise()
{
    //if a block is SQUARE TYPE, no change
    if(blockShape == SQUARE){
        return *this;
    }

    //turn left,x coordinate get negative
    BlockPiece result;
    result.blockShape = blockShape;
    for(int i=0; i<4; i++){
        result.getX(i, y(i));
        result.getY(i,-x(i));
    }
}

/**
 * @brief a function turn a block clockwise direction
 * @return a class BlockPiece
 */
BlockPiece BlockPiece::clockwise() const
{
    //if a block is SQUARE TYPE, no change
    if(blockShape == SQUARE){
        return *this;
    }

    //turn right, y coordinate get negative
    BlockPiece result;
    result.blockShape = blockShape;
    for(int i=0; i<4; i++){
        result.getX(i, -y(i));
        result.getY(i,x(i));
    }
}



