#include <iostream>
#include <sstream>
#include <string>

#include "Hero.h"

#define INVALID_INPUT "Invalid input\n\a"

void toLower(std::string &s){
    for(auto &i : s){
        i = tolower(i);
    }
}

void getInput(std::string &input){ // returns true if user wants to exit
    std::cout << "> ";
    std::getline(std::cin, input);
    toLower(input);
    if(input.substr(0,4)=="exit"){
        std::cout << "Are you sure?\n";
        std::cout << "> ";
        std::getline(std::cin, input);
        if(input[0]=='y'){
            // save info
            std::cout << "\nbye!\n\n";
            exit(EXIT_SUCCESS);
        }
    }
    return;
}

void getCaseSensitiveInput(std::string &input){
    std::cout << "> ";
    std::getline(std::cin, input);
}

bool isNumeric(const std::string &s){
    size_t i = (s[0] == '-' ? 1 : 0);
    
    for(; i<s.size();++i){
        if (!isdigit(s[i])){
            return false;
        }
    }
    return true;
}

// checks if input is a number and checks if number is positive or 0
void getNumericInput(int &num){ 
    std::string input;
    bool isNumber = false;
    do{
        getInput(input);
        isNumber = isNumeric(input);
        std::stringstream(input) >> num;

        if(!isNumber){
            std::cout << "Must input a number\n\a";
        }
        else if(num < 0){
            std::cout << "Must input a positive number or 0\n\a";
        }
    } while(!isNumber || num < 0);
    return;
}

void pointBuy(Hero* newGuy){
    std::cout << "\nLow Fantasy:      10\n";
    std::cout << "Standard Fantasy: 15\n";
    std::cout << "High Fantasy:     20\n";
    std::cout << "Epic Fantasy:     25\n\n"; 
    std::cout << "How many points are you allotted?\n";

    std::string input;
    bool pointBuyComplete=false;
    int points;

    // get number of points
    getNumericInput(points);
    
    int selection;
    int score;

    std::cout << "\nSelect an ability\n";
    std::cout << "0. Strength     \n";
    std::cout << "1. Dexterity    \n";
    std::cout << "2. Constitution \n";
    std::cout << "3. Intelligence \n";
    std::cout << "4. Wisdom       \n";
    std::cout << "5. Charisma     \n";           
    do{
    getNumericInput(selection);

    std::string abilityStr = "What score would you like to apply to ";

    switch(selection){
        case 0:
            abilityStr += "strength?\n";
            break;
        case 1:
            abilityStr += "dexterity?\n";  
            break;
        case 2:
            abilityStr += "constitution?\n";
            break;
        case 3:
            abilityStr += "intelligence?\n";
            break;
        case 4:
            abilityStr += "wisdom?\n";
            break;
        case 5:
            abilityStr += "charisma?\n";
            break;
        default:
            abilityStr = "Invalid input\n\a";
    }

    std::cout << abilityStr;

    getNumericInput(score);
    newGuy->setAbility(selection, score); 
    std::cout << "ability score " << newGuy->getAbility(selection) << std::endl;
    }while(1);
}

void setNewName(Hero* newGuy){ // returns true if user wants to exit
    std::string input;

    do{
        std::cout << "What is your character's name?\n";
        getCaseSensitiveInput(input);
        std::string name = input;
        std::cout << "You want your character to be called " << name << "? (y/n)\n";
        getInput(input);
    }while(input[0] != 'y');
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
            setNewName(newGuy);

            std::cout << "\nAwesome name!\n\n";
            // point buy or roll
            std::cout << "Point buy or roll for abilities?\n";
            do{
                getInput(input); 
                if(input.substr(0,5)!="point" && input.substr(0,4) != "buy" && input.substr(0,5) != "roll"){
                    std::cout << "Enter \'point buy\' or \'roll\'\n";
                }
            } while(input.substr(0,5)!="point" && input.substr(0,4) != "buy" && input.substr(0,5) != "roll");

            // point buy
            if(input.substr(0,5) == "point" || input.substr(0,4) == "buy"){
                pointBuy(newGuy);
            } // point buy 

            // roll for abilities
            else if(input.substr(0,4) == "roll"){
                std::cout << "ROLL\n";
            } // roll for abilities
        } // new character

        // edit character
        else if(input.substr(0,4) == "edit" || input.substr(0,7)== "existing"){
            // TODO
            std::cout << "What is your existing character's name?\n";
            std::cout << "I still need to code this part...\n";
        } // edit character

        else if(input[0] != 'n'){
            std::cout << "Invalid input\n\a";
        }
    }while(true);
    return 0;
}