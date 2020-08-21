#ifndef HERO_H
#define HERO_H

#include <string>
#include <vector>

class Hero{
    public:
    Hero();
    std::string getName();
    void setName(std::string);
    bool setAbility(int, int); // int1 - ability, int2 - score

    private:
    std::string name;
    std::vector<int> abilities; // 0 str, 1 dex, 2 con, 3 inf, 4 wis, 5 cha;
};

#endif