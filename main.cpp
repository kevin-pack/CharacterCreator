#include <iostream>
#include <string>
#include <sstream>

class Character{
    std::string name;

};

void toLower(std::string &s){
    for(auto &i : s){
        i = tolower(i);
    }
}

void getInput(std::string &input){
    std::cout << "> ";
    std::getline(std::cin, input);
    toLower(input);
}

int main(){ 
    std::cout << "\nWelcome to Kevin's Character Creator\n"; 
    std::cout << "------------------------------------\n";
    std::cout << "enter exit, quit, or q to quit\n\n"; 

    std::string input;
    do{
        std::cout << "Create new character or edit ?\n";
        getInput(input);
        if(input.substr(0,4) == "new"){
            std::cout << "Point buy or roll for abilities?\n";
            getInput(input);

            // point buy
            if(input.substr(0,5) == "point" || input.substr(0,4) == "buy"){
                std::cout << "How many points are you alloted?\n";
                getInput(input);
                size_t points;
                std::stringstream(input) >> points;
                std::cout << points << std::endl;
            }

            // roll for abilities
            else if(input.substr(0,4) == "roll"){
                std::cout << "ROLL\n";
            }

            else{
                std::cout << "Input not understood. Try again.\n";
            }
        }
    }while(input != "exit" && input != "quit" && input != "q");
    return 0;
}