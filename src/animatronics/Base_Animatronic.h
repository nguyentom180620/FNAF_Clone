#pragma once
#include <string>

class Base_Animatronic {
    std::string name;
    int level;
public:
    Base_Animatronic();
    Base_Animatronic(std::string n, int l);
    std::string getName();
};
