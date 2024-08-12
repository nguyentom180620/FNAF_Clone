#pragma once
#include <string>
#include "Adjacency_List.h"

class Base_Animatronic {
    std::string name;
    int level;
protected:
    Adjacency_List path;
public:
    Base_Animatronic();
    Base_Animatronic(std::string n, int l);
    std::string getName();
    const std::string getName() const;
    int getLevel();
    const int getLevel() const;
    const std::map<std::string, std::vector<std::string>>& getPath() const;
    bool operator==(Base_Animatronic const& base) const;
};
