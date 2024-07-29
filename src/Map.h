#pragma once
#include <string>
#include <iostream>
#include <unordered_map>

class Map {
    class Cam {
        std::string name;
        // Add animatronic vector
    public:
        Cam() {}
        Cam(std::string n) : name(n) {}
        std::string getName() {
            return name;
        }
    };
    std::unordered_map<std::string, Cam> cams{};
    // private methods
    bool isCam(std::string cam);
public:
    Map();
    void printCamContent(std::string cam);
};
