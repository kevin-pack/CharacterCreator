#include <iostream>
#include <sstream>
#include <string>

#include "Hero.h"

void toLower(std::string &s){
    for(auto &i : s){
        i = tolower(i);
    }
}

bool getInput(std::string &input){ // returns true if user wants to exit
    std::cout << "> ";
    std::getline(std::cin, input);
    toLower(input);
    if(input.substr(0,4)=="exit"){
        std::cout << "Are you sure?\n";
        std::cout << "> ";
        std::getline(std::cin, input);
        if(input[0]=='y'){
            return true;
        }
    }
    return false;
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

// checks if input is a number and checks if number is positive
bool getNumericInput(int &num){ 
    std::string input;
    bool isNumber = false, d0ne = false;
    do{
        d0ne = getInput(input);
        isNumber = isNumeric(input);
        std::stringstream(input) >> num;

        if(d0ne){
            return true;
        }
        if(!isNumber){
            std::cout << "Must input a number\n\a";
        }
        else if(num <= 0){
            std::cout << "Must input a positive number\n\a";
        }
    } while(!isNumber || num <= 0);

    return false;
}

bool pointBuy(Hero* newGuy){
    std::cout << "\nLow Fantasy:      10\n";
    std::cout << "Standard Fantasy: 15\n";
    std::cout << "High Fantasy:     20\n";
    std::cout << "Epic Fantasy:     25\n\n"; 
    std::cout << "How many points are you allotted?\n";

    std::string input;
    bool d0ne = false, pointBuyComplete=false;
    int points;

    // get number of points
    d0ne = getNumericInput(points);
    if(!d0ne){
        int selection = 0;

        while(!d0ne && !pointBuyComplete){
            std::cout << "\nSelect an ability\n";
            std::cout << "0. Strength     \n";
            std::cout << "1. Dexterity    \n";
            std::cout << "2. Constitution \n";
            std::cout << "3. Intelligence \n";
            std::cout << "4. Wisdom       \n";
            std::cout << "5. Charisma     \n";           

            d0ne = getNumericInput(selection);
            
        }        
    }
    return d0ne;
}

bool setNewName(Hero* newGuy){ // returns true if user wants to exit
    std::string input;

    do{
        std::cout << "What is your character's name?\n";
        getCaseSensitiveInput(input);
        std::string name = input;
        std::cout << "You want your character to be called " << name << "? (y/n)\n";
        bool d0ne = getInput(input);
        if(d0ne){
            return true;
        }
    }while(input[0] != 'y');

    return false;
}

int main(){ 
    std::cout << "\nWelcome to Kevin's Character Creator\n"; 
    std::cout << "------------------------------------\n";
    std::cout << "enter exit if u want to exit\n\n";

    std::string input;
    bool d0ne = false;

    do{
        std::cout << "Create new character or edit existing character?\n";

        d0ne = getInput(input);

        // new character
        if(input.substr(0,4) == "new" || input.substr(0,6) == "create"){
            Hero* newGuy = new Hero();

            // get name
            d0ne = setNewName(newGuy);

            if(!d0ne){
                std::cout << "\nAwesome name!\n\n";
                bool doneAbilities;
                // point buy or roll
                do{
                    std::cout << "Point buy or roll for abilities?\n";
                    d0ne = getInput(input);

                    // point buy
                    if((!d0ne) && (input.substr(0,5) == "point" || input.substr(0,4) == "buy")){
                        d0ne = pointBuy(newGuy);
                        doneAbilities=true;
                    } // point buy 

                    // roll for abilities
                    else if(input.substr(0,4) == "roll"){
                        std::cout << "ROLL\n";
                        doneAbilities=true;
                    } // roll for abilities

                    // bad input
                    else if (!d0ne && input[0] != 'n'){
                        std::cout << "Invalid input\n\a";
                    }
                } while(!d0ne && !doneAbilities); // point buy or roll
            } // abilities
        } // new character

        // edit character
        else if(input.substr(0,4) == "edit" || input.substr(0,7)== "existing"){
            // TODO
            std::cout << "What is your existing character's name?\n";
            std::cout << "I still need to code this part...\n";
        } // edit character

        else if(!d0ne && input[0] != 'n'){
            std::cout << "Invalid input\n\a";
        }
    }while(!d0ne);
    
    std::cout << "\nbye!\n\n";
    return 0;
}