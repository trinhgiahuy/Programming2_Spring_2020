/* Game15 (or puzzle 15) : Template code
 *
 * Desc:
 *  This program generates a 15 puzzle. The board is SIZE x SIZE,
 * (original was 4x4) and every round the player chooses a direction and
 * a number tile, making the given tile to be moved to the given direction.
 *  Game will end when the numbers 1-15 (1-16) are in the ascending order,
 * starting from top left and proceeding row by row.
 * Empty space is represented by the number 16 in the code (constant EMPTY)
 * and by dot when printing the game board.
 *
 * Program author ( Fill with your own info )
 * Name: Teemu Teekkari
 * Student number: 123456
 * UserID: teekkart ( Necessary due to gitlab folder naming. )
 * E-Mail: teemu.teekkari@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */

#include "board.hh"
bool check_input(char input){
    if(input!="y"|| input!="n"||input!="q"){
        //cout<<"Unknown choice: "<<input;
        return false;
    }else{
        return true;
    }
}
bool solvability(){
   std::vector<std::vector<unsigned int >> grid_cpt(this->grid_);
   std::vector<std::vector<unsigned int >> grid_tem;
   int row=get_coordinate(16).first;
   int column=get_coordinate(16).second;
   int count;
   while(row!=SIZE-1){
        std::swap(grid_cpt[row][column],grid_cpt[row+1][column]);
        ++row;
   }

for(unsigned int u=0;u<SIZE;u++){
    for(unsigned int v=0;v<SIZE<;v++){
        if(grid_cpt[u][v]!=16){
               grid_tem.push_back(grid_cpt[u][v]);
           }
       }
   }
}

int main()
{
    char input;
    cout<<"Random initialization (y/n)"<<endl;
    cin>>input;
    while (!check_input(input)) {
        cout<<"Unknown choice: "<<input;
        cout<<"Random initialization (y/n)"<<endl;
    }
    if(input=="y"){
        int seed;
        cout<<"Enter a seed value (or an empty line): "<<endl;
        cin>>seed;
        solvability();
        std::vector<std::vector<unsigned int>>A[SIZE][SIZE];
        Board A;
        A.my_shuffle();


    }else{
        if(input=="n"){

        }else{

        }
    }

    return EXIT_SUCCESS;
}
