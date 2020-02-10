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
 * Name: Trinh Gia Huy
 * Student number: 290290
 * UserID: bdgitr
 * E-Mail: giahuy.trinh@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */
#include<iostream>
#include "board.hh"
#include<string>
#include<algorithm>
#include<ctime>
#include<sstream>
/*----------------------------------------------------*/
// a function that check player's input and return a input_model(string)
std::string check_input(){
    std::string input_model = "";

    while( true ){
        std::cout << "Random initialization (y/n): ";
        getline(std::cin, input_model);
        if ( input_model != "y" && input_model != "Y" && input_model != "n" && input_model != "N" ){
            std::cout << "Unknown choice: " << input_model << std::endl;
            continue;
        }
        break;
    }

    return input_model;
}

/*----------------------------------------------------*/
// a function that control the game's flow and return the boolean value
void game_control(Board& board){

    while( true ){
           std::cout << "Dir (command, number): ";
           std::string input="";
           std::string digit="";
           std::cin >> input;
           if ( input == "q" ){
               return;
           }
           std::cin >> digit;
           if ( input != "a" && input != "s" && input != "d" && \
               input != "w" && input != "q" ){

               std::cout << "Unknown command: " << input << std::endl;
           }
           else  if ( stoi(digit) > 16 || stoi(digit) < 1 ){
               std::cout << "Invalid number: " << stoi(digit) << std::endl;
           }
           else{
               board.micro_controller(input, board.get_coordinate(stoi(digit)) );

               if ( board.winning() ){
                   board.print();
                   std::cout << "You won!" << std::endl;
                   break;

               }
           }

           board.print();
       }
}

/*--------------------------------------------*/
// a function that check player's input whether is any numbers from 1- 16 is missing
bool find_missing_num(std::vector<unsigned int>data){
    std::sort(data.begin(),data.end());
    for(unsigned int index=0;index<EMPTY;){
        if(data[index]-index!=1){
            std::cout<<"Number "<<index+1<<" is missing"<<std::endl;
            return false;
        }
        ++index;
    }
    return true;
}

/*----------------------------------------------------*/
// a function that continue the game's flow if player's command is no
bool game_determine_mode(){
    std::cout<<"Enter the numbers 1-16 in a desired order (16 means empty):"<<std::endl;
    std::vector<unsigned int> data(16,0);

    for(int index=0;index<EMPTY;++index){
        std::cin>>data[index];
    }
    if(find_missing_num(data)!= true){
        return false;
    }
    Board board(data);
    if(board.solvability()){
        std::cout<<"Game is solvable: Go ahead!"<<std::endl;
    }else{
        std::cout<<"Game is not solvable. What a pity."<<std::endl;
        return true;
    }
    board.print();
    game_control(board);
    return true;
}


/*----------------------------------------------------*/

/*_____________________________________________________*/
// a function that randomize the puzzle
void game_random(){
    std::cout << "Give a seed value or an empty line: ";
    std::string seed = "";
    getline(std::cin, seed);
    if ( seed == "" ){
        seed = std::to_string( time(NULL) );
    }
    Board board( stoi(seed) );
    if ( board.solvability() ){
        std::cout << "Game is solvable: Go ahead!" << std::endl;
    }
    else{
        std::cout << "Game is not solvable. What a pity." << std::endl;
        return;
    }

    board.print();

    game_control( board );
}

/*----------------------------------------------------------*/
int main(){
    std::string input_mode="";
    input_mode=check_input();
    if(input_mode=="y"){
        game_random();
    }else{
        if(!game_determine_mode()){
            return EXIT_FAILURE;}
    }
    return EXIT_SUCCESS;
}
