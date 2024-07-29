#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "../animatronics/Base_Animatronic.h"

class Map {
    class Cam {
        std::string name;
        std::vector<Base_Animatronic*> animatronics;
    public:
        Cam();
        Cam(std::string n);
        std::string getName();
        void addAnimatronic(Base_Animatronic& base);
        std::vector<std::string> getAnimatronicNames();
    };
    std::unordered_map<std::string, Cam> cams{};
    Base_Animatronic base;
    // private methods
    bool isCam(std::string cam);
public:
    Map();
    void printCamContent(std::string cam);
};
