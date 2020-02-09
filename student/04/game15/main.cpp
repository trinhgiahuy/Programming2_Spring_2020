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
#include<iostream>
#include "board.hh"
bool check_input(std::string input){
    if(input!="y"|| input!="n"||input!="q"){
        //cout<<"Unknown choice: "<<input;
        return false;
    }else{
        return true;
    }
}

int main()
{
    std::string input;
    std::cout<<"Random initialization (y/n)"<<std::endl;
    getline(std::cin,input);
    while (!check_input(input)) {
        std::cout<<"Unknown choice: "<<input;
        std::cout<<"Random initialization (y/n)"<<std::endl;
        if(input=="q"){
            return EXIT_SUCCESS;
        }else{
            continue;
        }

    }
    if(input=="y"){
        int seed;
        std::cout<<"Enter a seed value (or an empty line): "<<std::endl;
        std::cin>>seed;
        //solvability();
        std::vector<std::vector<unsigned int>>A[SIZE][SIZE];



    }else{
        if(input=="n"){

        }else{

        }
    }

    return EXIT_SUCCESS;
}
