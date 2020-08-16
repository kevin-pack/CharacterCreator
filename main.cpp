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

bool isNumeric(const std::string &s){
    for(auto i : s){
        if (!isdigit(i)){
            return false;
        }
    }
    return true;
}



int main(){ 
    std::cout << "\nWelcome to Kevin's Character Creator\n"; 
    std::cout << "------------------------------------\n";
    std::cout << "enter exit... if u want to exit\n\n"; 

    std::string input;

    do{
        std::cout << "Create new character or edit existing character?\n";
        getInput(input);

        // new character
        if(input.substr(0,4) == "new" || input.substr(0,6) == "create"){
            // get name
            do{

            }while(input!="exit");

            if(input!="exit"){
                // point buy or roll
                do{
                    std::cout << "Point buy or roll for abilities?\n";
                    getInput(input);

                    // point buy
                    if(input.substr(0,5) == "point" || input.substr(0,4) == "buy"){
                        std::cout << "\nLow Fantasy:      10\n";
                        std::cout << "Standard Fantasy: 15\n";
                        std::cout << "High Fantasy:     20\n";
                        std::cout << "Epic Fantasy:     25\n\n"; 
                        std::cout << "How many points are you allotted?\n";

                        // # of points input
                        do{
                            getInput(input);
                            if(isNumeric(input)){
                                size_t points;
                                std::stringstream(input) >> points;
                            }
                            else{
                                std::cout << "Invalid input\n";
                            }
                            
                        } while(input != "exit");
                    } // point buy 

                    // roll for abilities
                    else if(input.substr(0,4) == "roll"){
                        std::cout << "ROLL\n";
                    } // roll for abilities

                    // bad input
                    else if(input != "exit"){
                        std::cout << "Invalid input\n";
                    }
                } while(input != "exit"); // point buy or roll? 
            } // input!=exit
        } // new character

        // edit character
        else if(input.substr(0,4) == "edit"){
            // TODO
        } // edit character

        else if(input != "exit"){
            std::cout << "Invalid input\n\a";
        }
    }while(input != "exit");

    return 0;
}