#pragma once
#include <string>

class Base_Animatronic {
    std::string name;
    int level;
public:
    Base_Animatronic();
    Base_Animatronic(std::string n, int l);
    std::string getName();
    const std::string getName() const;
    int getLevel();
    const int getLevel() const;
    bool operator==(Base_Animatronic const& base) const;
};
