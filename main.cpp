#include <iostream>
#include <sstream>
#include <string>

#include "Hero.h"

#define INVALID_INPUT "Invalid input\n\a"
#define ERR -5

const std::vector<std::string> abilityNames = {"strength", "dexterity", "constitution", "intelligence", "wisdom", "charisma"};
const std::vector<int> abilityCost = {ERR, ERR, ERR, ERR, ERR, ERR, ERR, -4, -2, -1, 0, 1, 2, 3, 5, 7, 10, 13, 17};

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

int getAbilitySelection(Hero* newGuy){

    int selection;

    std::cout << "\nSelect an ability\n";
    std::cout << "0. Strength           \n";
    std::cout << "1. Dexterity          \n";
    std::cout << "2. Constitution       \n";
    std::cout << "3. Intelligence       \n";
    std::cout << "4. Wisdom             \n";
    std::cout << "5. Charisma           \n";           
    std::cout << "6. View Cost Table    \n";
    std::cout << "7. View ability scores\n";

    do{
        getNumericInput(selection);
        if(selection == 6){
            std::cout << "\n| Score | Cost | Modifier |\n";
            std::cout << "|   7   |  -4  |    -2    |\n";
            std::cout << "|   8   |  -2  |    -1    |\n";
            std::cout << "|   9   |  -1  |    -1    |\n";
            std::cout << "|  10   |   0  |     0    |\n";
            std::cout << "|  11   |   1  |     0    |\n";
            std::cout << "|  12   |   2  |    +1    |\n";
            std::cout << "|  13   |   3  |    +1    |\n";
            std::cout << "|  14   |   5  |    +2    |\n";
            std::cout << "|  15   |   7  |    +2    |\n";
            std::cout << "|  16   |  10  |    +3    |\n";
            std::cout << "|  17   |  13  |    +3    |\n";
            std::cout << "|  18   |  17  |    +4    |\n\n";        
        }
        else if(selection == 7){
            std::cout << std::endl;
            for(size_t i=0; i < 6; ++i){
                std::cout << abilityNames[i] << ": " << newGuy->getAbility(i) << std::endl;
            }
            std::cout << std::endl;
        }
        if(selection > 7){
            std::cout << "User must input a number 0 through 7\n\a";
        }
    } while(selection > 7);

    return selection;
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
    
    int score;
    int selection;
    
    do{
        std::cout << "\nPoints remaining: " << points << std::endl;
        selection = getAbilitySelection(newGuy);
        std::cout << "What score would you like to apply to " << abilityNames[selection] << "?" << std::endl;

        getNumericInput(score);

        if(score < 7){
            std::cout << "\nScore must be greater than or equal to 7 and less than or equal to 18\n\a";
        }
        else if(score > 18){
            std::cout << "\nScore must be less than or equal to 18 and greater than or equal to 7\n\a";
        }
        else if(points - abilityCost[score] >= 0){
            // if ability has already been changed, refund points
            if(newGuy->getAbility(selection) != 10){
                std::cout << "Refunding points\n";
                points += abilityCost[newGuy->getAbility(selection)];
            }
            // set ability and deduct points
            newGuy->setAbility(selection, score); 
            std::cout << abilityNames[selection] << " ability score: " << newGuy->getAbility(selection) << std::endl;
            points -= abilityCost[score];
        }
        else if (points - abilityCost[score] < 0){
            std::cout << "\nYou don't have enough points!\n\a";
        }
        else{
            std::cout << INVALID_INPUT;
        }
    } while(points > 0);

    std::cout << "Ability scores assigned!\n";
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

        else if(input == "n" || input=="no"){
            std::cout << "Invalid input\n\a";
        }
    }while(true);
    return 0;
}