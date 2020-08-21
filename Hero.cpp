#include "Hero.h"

#define DEFAULT_SCORE 10
#define NUM_ABILITIES 6

Hero::Hero() : abilities(NUM_ABILITIES) {}

std::string Hero::getName(){
    return name;
}

bool Hero::setAbility(int abilityIndex, int score){
    if(score > 0){
        this->abilities[abilityIndex] = score; 
        return true;
    }
    return false;
}
void Hero::setName(std::string n){
    this->name = n;
}