/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *
 * Program author ( Fill with your own info )
 * Name: Teemu Teekkari
 * Student number: 123456
 * UserID: teekkart ( Necessary due to gitlab folder naming. )
 * E-Mail: teemu.teekkari@tuni.fi
 *
 * Notes:
 *
 * */

#include "board.hh"
#include <iostream>
#include <iomanip>
#include<random>

//const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;

void Board::print()
{
    for(unsigned int x = 0; x < SIZE; ++x)
    {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for(unsigned int y = 0; y < SIZE; ++y)
        {
            std::cout << "|" << std::setw(PRINT_WIDTH - 1);
            if(grid_.at(x).at(y) != EMPTY)
            {
                std::cout << grid_.at(x).at(y);
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

void Board::my_shuffle(std::vector<unsigned int> &numbers, int seed){
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i)
    {
        unsigned int random_index = distr(randomEng);
        unsigned int temp = numbers.at(i);
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }
}
/*----------------------------------------------------------------*/
bool Board::solvability(){
   std::vector<std::vector<unsigned int >> grid_cpt(Board.grid_);
   std::vector<std::vector<unsigned int >> grid_tem;
   int row=get_coordinate(16).first;
   int column=get_coordinate(16).second;
   int count;
   while(row!=SIZE-1){
        std::swap(grid_cpt[row][column],grid_cpt[row+1][column]);
        ++row;
   }

for(unsigned int u=0;u<SIZE;){
    for(unsigned int v=0;v<SIZE<;){
        if(grid_cpt[u][v]!=16){
               grid_tem.push_back(grid_cpt[u][v]);
        }else{
            continue;
        }
        v++;
       }
      u++;
   }
}
/*------------------------------------------------------------*/
//constructor1
Board::Board(int seed){
    std::vector<unsigned int> model_grid(16,0);

    for (int i=0;i<EMPTY;i++){
        model_grid[i]=i+1;
    }
    my_shuffle(model_grid,seed);
}
/*------------------------------------------------------------*/
//function that return the 2 dimensions vector that contains the u-v coordinate
std::pair<unsigned int, unsigned int>Board::get_coordinate(unsigned int index_coordinate){
    std::pair<unsigned int, unsigned int> lattest(0,0);
    for(unsigned int u=0;u<SIZE;){
        for(unsigned int v=0;v<<SIZE;){
            if(this->grid_[u][v]==index_coordinate){
               lattest.first=u;
               lattest.second=v;
            }else{
                continue;
            }
        v++;
        }
        u++;
    }
    return lattest;
}
/*--------------------------------------------------------------*/
void Board::control(std::string direct,std::pair<unsigned int, unsigned int> coordinate){
    int row=coordinate.first;
    int column=coordinate.second;
    if(direct=="w"){
        if(row==0||Board.grid_[row][column-1]!=16){
            std::cout<<"Impossible direction: "<<direct<<std::endl;
        else{
        std::swap(Board.grid_[row][column],Board.grid_[row-1][column]);}
        }
    }
    if(direct="s"){
        move_down();
    }
    if(direct=="a"){
        move_left();
    }
    if(direct=="d"){
        move_right();
    }
}
/*______________________________________________________________*/
//void Board::move_up(){
//    if(row==0||Board.grid_[row][column-1]!=16){
//        std::cout<<"Impossible direction: "<<direct<<std::endl;
//        else{
//    std::swap(Board.grid_[row][column],Board.grid_[row-1][column]);}
//    }
void Board::move_down(){
     std::swap(Board.grid_[row][column], Board.grid[row + 1][column] );
}
void Board::move_left(){
      std::swap( Board.grid[row][column], Board.grid[row][column];}
void Board::move_right(){
     std::swap( Board.grid[row][column],Board.grid[row][column +1]);
}
/*_____________________________________________________________*/
bool Board::winning_(){
    for (unsigned int u=0;u<SIZE;u++){
        for(unsigned int v=0;v<SIZE;){
            if(Board.grid_[u][v]==u*SIZE+v+1){
                return true;
            }
            v++;
        }
        u++;
    }
    return false;
}





