#include "Hero.h"

#define DEFAULT_SCORE 10
#define NUM_ABILITIES 6

Hero::Hero() : abilities(NUM_ABILITIES, DEFAULT_SCORE) {}

std::string Hero::getName(){
    return this->name;
}
int Hero::getAbility(int index){
    return this->abilities[index];
}
bool Hero::setAbility(int abilityIndex, int score){
    if(score >= 7){
        this->abilities[abilityIndex] = score; 
        return true;
    }
    return false;
}
void Hero::setName(std::string n){
    this->name = n;
}