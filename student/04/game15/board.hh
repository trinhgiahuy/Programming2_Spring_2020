/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *  Describes a two-dimensional grid for puzzle 15 with necessary functions.
 *
 * Program author ( Fill with your own info )
 * Name: Trinh Gia Huy
 * Student number: 290290
 * UserID: bdgitr
 * E-Mail: giahuy.trinh@tuni.fi
 *
 * Notes:
 *
 * */

#ifndef BOARD_HH
#define BOARD_HH
#include <vector>
#include<string>

const int SIZE = 4;

class Board
{
public:
    // For creating and initializing the grid, you have at least two choices:
    // 1. Implement a constructor that fills the game grid with empties or such
    // and two initialize methods
    // 2. Implement two constructors, one for each initialization way
    Board(std::vector<unsigned int>& content);
    Board (int seed);


    // Prints the game grid
    void print();

    // More methods
    std::pair<unsigned int,unsigned int>get_coordinate(unsigned int index_coordinate);

    void control(std::string direct,std::pair<unsigned int, unsigned int> coordinate);
    void solvability();
    void win();
private:
    // Shuffles the numbers vector by using seed as a seed value
    void my_shuffle(std::vector<unsigned int>& numbers, int seed);

    // Game grid for the 15 puzzle
    std::vector<std::vector<unsigned int>> grid_;

    // More attributes/methods
};

#endif // BOARD_HH
