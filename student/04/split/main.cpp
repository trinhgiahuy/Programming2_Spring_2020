#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include<ctype.h>
std::vector<std::string> split(std::string line, char model, bool truth =false){
    std::vector <std::string> result ;
    std::string model_string="";
//    if(truth==false){
    for(unsigned int index=0;index<line.size();index++){

        if(line[index]!=model) {
            model_string+=line[index];
            continue;
        }else{
        result.push_back(model_string);
        model_string.clear();
        }
        if(line[line.length()]==model){
            result.push_back(model_string);
        }

//        if(line[index]==model){
//            result.push_back(model_string);
//            model_string.clear();
//            continue;

//        }
//        else{
//            model_string+=line[index];
//            //result.push_back(model_string);
//        }
//        //result.push_back(model_string);

//    }
//    }else{
//       continue;
//    }
}
    return result;
}
//    char element;
//    for(auto element : line ){
//        if(element==model){

//        }
//    }

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

//    std::vector< std::string > parts_no_empty  = split(line, separator, true);
//    std::cout << "Splitted string ignoring empty parts: " << std::endl;
//    for( auto part : parts_no_empty ) {
//        std::cout << part << std::endl;
//    }
}
