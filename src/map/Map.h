#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../animatronics/Base_Animatronic/Base_Animatronic.h"

class Map {
public:
    class Cam {
        std::string name;
        std::vector<Base_Animatronic*> animatronics;
    public:
        Cam();
        Cam(std::string n);
        std::string getName();
        const std::string getName() const;
        void addAnimatronic(Base_Animatronic& base);
        void removeAnimatronic(Base_Animatronic& base);
        std::vector<std::string> getAnimatronicNames();
        const std::vector<std::string> getAnimatronicNames() const;
        bool operator==(Cam const& rhsCam) const;
    };
private:
    std::unordered_map<std::string, Cam> cams{};
    // private methods
    bool isCam(const std::string& cam);
    const std::unordered_map<std::string, Cam> getCams() const;
public:
    Map();
    Cam& accessCam(const std::string& cam_name);
    const Cam& accessCam(std::string& cam_name) const;
    Cam find(Base_Animatronic const& base);
    const Cam find(Base_Animatronic const& base) const;
    void addAnimatronic(Base_Animatronic& base);
    void addFoxy(Base_Animatronic& base);
    void moveAnimatronic(Base_Animatronic& base, Cam& oldCam, Cam& newCam);
    void printCamContent(std::string& cam);
    bool animatronicAtDoor(Base_Animatronic& base, std::string door);
};
