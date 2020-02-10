/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *
 * Program author ( Fill with your own info )
 * Name: Trinh Gia Huy
 * Student number: 290290
 * UserID: bdgitr ( Necessary due to gitlab folder naming. )
 * E-Mail: giahuy.trinh@tuni.fi
 *
 * Notes:
 *
 * */

#include "board.hh"
#include <iostream>
#include <iomanip>
#include<random>
#include<algorithm>

//const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;

void Board::print() const
{
    for(unsigned int x = 0; x < SIZE; ++x)
    {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for(unsigned int y = 0; y < SIZE; ++y)
        {
            std::cout << "|" << std::setw(PRINT_WIDTH - 1);
            if(this->grid_.at(x).at(y) != EMPTY)
            {
                std::cout << this->grid_.at(x).at(y);
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
/*--------------------------------------------------------------*/
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
   std::vector<std::vector<unsigned int >> grid_cpt(this->grid_);
   std::vector<unsigned int>grid_tem;
   int row=get_coordinate(16).first;
   int column=get_coordinate(16).second;
   int count=0;
   while(row!=SIZE-1){
        std::swap(grid_cpt[row][column],grid_cpt[row+1][column]);
        ++row;
   }

for(int u=0;u<SIZE;u++){
    for(int v=0;v<SIZE;v++){
        if(grid_cpt[u][v]!=16){
               grid_tem.push_back(grid_cpt[u][v]);

        }

       }

}
//int count=0;
for( unsigned int u=0;u<grid_tem.size()- 1;){

    for ( unsigned int v = u+1; v< grid_tem.size();){

        if ( grid_tem[v] < grid_tem[u] ){
                ++count;
            }

        v++;
        }

    u++;

}
return (count % 2 == 0);
}
/*------------------------------------------------------------*/
Board::Board(std::vector<unsigned int>&data){
    fix_data(data); 
}
/*------------------------------------------------------------*/
//constructor1
Board::Board(int seed){
    std::vector<unsigned int> model_grid(16,0);

    for (int i=0;i<EMPTY;++i){
        model_grid[i]=i+1;
//        i++;
    }

    my_shuffle(model_grid,seed);

    fix_data(model_grid);
}
/*------------------------------------------------------------*/
//function that return the 2 dimensions vector that contains the u-v coordinate
std::pair<unsigned int, unsigned int>Board::get_coordinate(unsigned int index_coordinate){
    std::pair<int, int> lattest(0,0);
    for(unsigned int u=0;u<SIZE;++u){

        for(unsigned int v=0;v<<SIZE;++v){

            if(this->grid_[u][v]==index_coordinate){
               lattest.first=u;
               lattest.second=v;
               return lattest;
            }
        }
    }
    return lattest;
}
/*--------------------------------------------------------------*/
void Board::micro_controller(std::string direct,std::pair<unsigned int, unsigned int> coordinate){
    int row=coordinate.first;
    int column=coordinate.second;
    //std::string a=std::cout<<"Impossible direction: "<<direct<<std::endl;

    if(direct=="w"){
        if(row==0||this->grid_[row-1][column]!=16){
            std::cout<<"Impossible direction: "<<direct<<std::endl;}
        else{
            std::swap(this->grid_[row][column],this->grid_[row-1][column]);}
        }


    if(direct=="s"){
        if(row==SIZE-1||this->grid_[row+1][column]!=16){
            std::cout<<"Impossible direction: "<<direct<<std::endl;
        }else{
            std::swap(this->grid_[row][column],this->grid_[row + 1][column]);

    }
}


    if(direct=="a"){
        if(column==0||this->grid_[row][column - 1] != 16 ){
            std::cout<<"Impossible direction: "<<direct<<std::endl;
        }else{
            std::swap(this->grid_[row][column],this->grid_[row][column-1]);
        }
    }


    if(direct=="d"){
        if(column==SIZE-1||this->grid_[row][column+1] != 16 ){
            std::cout<<"Impossible direction: "<<direct<<std::endl;
        }else{
            std::swap(this->grid_[row][column],this->grid_[row][column+1]);
        }
    }
}

/*______________________________________________________________*/
//void Board::move_up(){
//    if(row==0||Board.this->grid_[row][column-1]!=16){
//        std::cout<<"Impossible direction: "<<direct<<std::endl;
//        else{
//    std::swap(Board.this->grid_[row][column],Board.this->grid_[row-1][column]);}
//    }
//void Board::move_down(){
//     std::swap(this->grid_[row][column], Board.grid[row + 1][column] );
//}
//void Board::move_left(){
//      std::swap( Board.grid[row][column], Board.grid[row][column];}
//void Board::move_right(){
//     std::swap( Board.grid[row][column],Board.grid[row][column +1]);
//}
/*_____________________________________________________________*/

bool Board::winning(){
    for (unsigned int u=0;u<SIZE;++u){
        for(unsigned int v=0;v<SIZE;++v){
            if(this->grid_[u][v]!=u*SIZE+v+1){
                return false;
            }
         //   v++;
        }
        //u++;
    }
    return true;
}
/*-------------------------------------------------------------*/
void Board::fix_data(const std::vector<unsigned int>& data){
    std::vector<unsigned int> row_data;
    for(unsigned int u=0;u<SIZE;++u){
        for (unsigned int v=0;v<SIZE;++v){
            row_data.push_back(data[u*SIZE+v]);
            //v++;
        }
        this->grid_.push_back(row_data);
        //u++;
    }
}

/*--------------------------------------------------------*/


