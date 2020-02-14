#include <iostream>
#include <fstream>
#include<string>
using namespace std;
int main(){
    std::string file_name ="";
    std::string file_name_1 ="";
    cout<<"Input file: ";
    getline(cin,file_name);
    cout<<"Output file: "<<std::endl;
    ifstream file_object(file_name);
    getline(cin,file_name_1);
    if(not file_object){
        cout<<"Error! The file "<<file_name<<"cannot be opened."<<std::endl;

    }else{
        std::string line;
        int num=1;
        while (getline(file_object,line)) {
            cout<<num<<" "<<line<<endl;
            num+=1;
        }
        file_object.close();
    }

}
