#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <ctime>

#include "Hero.h"

#define INVALID_INPUT "Invalid input\n\a"
#define ERR -69

const std::vector<std::string> abilityNames = {"strength", "dexterity", "constitution", "intelligence", "wisdom", "charisma"};
const std::vector<int> abilityCost = {ERR, ERR, ERR, ERR, ERR, ERR, ERR, -4, -2, -1, 0, 1, 2, 3, 5, 7, 10, 13, 17};
const std::vector<int> abilityModifier = {ERR, -5, -4, -4, -3, -3, -2, -2, -1, -1, 0, 0, 1, 1, 2, 2, 3, 3, 4};

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

void printAbilityTable(){
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
            printAbilityTable();
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
void rollAbilities(Hero* newGuy){
    // roll six dice
    std::cout << "Rolling four dice for each ability, discarding the lowest roll, and adding the remaining three rolls together to determine your scores\n";
    std::vector<int> randAbilities(6);
    std::vector<int> nums(4);
    int minNum=INT_MAX, score;
    size_t minIndex;


    for(size_t i=0; i < randAbilities.size(); ++i){
        minNum=INT_MAX;
        score = 0;
        // get 4 random numbers
        for(size_t j=0; j < nums.size(); ++j){
            nums[j] = (rand() % 6) + 1;
            //std::cout << nums[j] << std::endl;
            if(nums[j] < minNum){
                minNum = nums[j];
                minIndex=j;
                //std::cout << "minNum: " << nums[minIndex] << std::endl;
            }
        }
        //std::cout << "---\n";
        // discard lowest number
        nums[minIndex]=0;
        // add other numbers together and assign to list
        for(size_t j=0; j < nums.size(); ++j){
            score += nums[j];
        }

        if(score >= 7){ 
            randAbilities[i] = score;
        }
        else{
            randAbilities[i] = 7;
        }
    }
    std::cout << "Ability scores   Modifier\n";
    std::cout << "--------------   --------\n";
    for(size_t i=0; i<randAbilities.size(); ++i){
        std::cout << std::setw(13) << std::left << abilityNames[i] << randAbilities[i] << "     (" << abilityModifier[randAbilities[i]] << ")" << std::endl;
    }

    std::cout << "\nDo you want to re-assign these scores?\n";

    std::string input;

    getInput(input);
    if(input[0] == 'y'){
        bool doneAssigning = false;
        int inputScore, abilityIndex=0;

        while(!doneAssigning){
            std::cout << "scores: ";
            for(auto score : randAbilities){
                std::cout << score << ", ";
            }

            std::cout << std::endl;
            std::cout << abilityNames[abilityIndex] << " ";
            getNumericInput(inputScore);

            std::vector<int>::iterator numIter = std::find(randAbilities.begin(), randAbilities.end(), inputScore);

            if(numIter != randAbilities.end()){
                //std::cout << "Assigning " << inputScore << " to " << abilityNames[abilityIndex] << std::endl;
                newGuy->setAbility(abilityIndex, inputScore);
                randAbilities.erase(numIter);
                abilityIndex++;
            }
            else{
                std::cout << inputScore << " not found in list of ability scores generated.\n";
            }

            if(randAbilities.empty()){
                doneAssigning = true;
            }
        }
    }
    else{
        std::cout << "Leaving scores as-is\n";
    }
}

void pointBuy(Hero* newGuy){
    std::cout << "\nLow Fantasy:      10\n";
    std::cout << "Standard Fantasy: 15\n";
    std::cout << "High Fantasy:     20\n";
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
    // initialize random seed
    srand(time(NULL));

    std::cout << "\nWelcome to Pathfinder Character Creator\n"; 
    std::cout << "------------------------------------\n";
    std::cout << "enter exit if u want to exit\n\n";

    std::string input;
    bool d0ne = false;

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
                rollAbilities(newGuy);
            } // roll for abilities
        } // new character

        // edit character
        else if(input.substr(0,4) == "edit" || input.substr(0,7)== "existing"){
            // TODO
            std::cout << "What is your existing character's name?\n";
            std::cout << "I still need to code this part...\n";
        } // edit character

        else{
            std::cout << "Invalid input\n\a";
        }
        
        std::cout << "Done?\n";
        getInput(input);
        d0ne = input[0] == 'y';

    }while(!d0ne);
    return 0;
}