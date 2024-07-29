#pragma once
#include <string>
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
public:
    Map();
    bool isCam(std::string cam);
};
