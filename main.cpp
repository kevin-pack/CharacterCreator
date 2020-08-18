#include <iostream>
#include <sstream>
#include <string>

#include "Hero.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

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

void getCaseSensitiveInput(std::string &input){
    std::cout << "> ";
    std::getline(std::cin, input);
}

bool isNumeric(const std::string &s){
    for(auto i : s){
        if (!isdigit(i)){
            return false;
        }
    }
    return true;
}

bool setNewName(Hero* newGuy){
    std::string input;
    do{
        std::cout << "What is your character's name?\n";
        getCaseSensitiveInput(input);
        std::string name = input;
        std::cout << "Just to confirm, you want your character to be called " << name << "? (y/n)\n";
        getInput(input);

        if(input[0]=='y'){
            newGuy->setName(name);                  
        }
        else if(input == "exit"){
            return false;
        }
    }while(input[0] != 'y');

    return true;
}

bool pointBuy(Hero* newGuy){
    std::cout << "\nLow Fantasy:      10\n";
    std::cout << "Standard Fantasy: 15\n";
    std::cout << "High Fantasy:     20\n";
    std::cout << "Epic Fantasy:     25\n\n"; 
    std::cout << "How many points are you allotted?\n";

    // # of points input
    std::string input;

    do{
        getInput(input);
        if(isNumeric(input)){
            size_t points;
            std::stringstream(input) >> points;
            if(points > 0){
                std::cout << "Strength:     ";
                std::cout << "Dexterity:    ";
                std::cout << "Constitution: ";
                std::cout << "Intelligence: ";
                std::cout << "Wisdom:       ";
                std::cout << "Charisma:     ";
            }
        }
        else if(input == "exit"){
            return false;
        }
        else{
            std::cout << "Invalid input\n";
        }
        
    } while(input != "exit");
    return true;
}

int main(){ 
    std::cout << "\nWelcome to Kevin's Character Creator\n"; 
    std::cout << "------------------------------------\n";
    std::cout << "enter exit if u want to exit\n\n"; 

    std::string input;

    do{
        std::cout << "Create new character or edit existing character?\n";
        getInput(input);

        // new character
        if(input.substr(0,4) == "new" || input.substr(0,6) == "create"){
            Hero* newGuy = new Hero();
            // get name
            if(!setNewName(newGuy)){
                input = "exit";
            }
            else{
                std::cout << "Cool name!\n";
            }
            if(input!="exit"){
                // point buy or roll
                do{
                    std::cout << "Point buy or roll for abilities?\n";
                    getInput(input);

                    // point buy
                    if(input.substr(0,5) == "point" || input.substr(0,4) == "buy"){
                        if(!pointBuy(newGuy)){
                            input = "exit";
                        }
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
        else if(input.substr(0,4) == "edit" || input.substr(0,7)== "existing"){
            // TODO
            std::cout << "What is your existing character's name?\n";
            std::cout << "I still need to code this part...\n";
        } // edit character

        else if(input != "exit"){
            std::cout << "Invalid input\n\a";
        }
    }while(input != "exit");

    return 0;
}