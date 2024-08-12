#pragma once
#include <random>
#include "../../map/Map.h"
#include "../../animatronics/Bonnie/Bonnie.h"

class Game_Night {
    // Idea: Have a nullptr for the office. If the pointer contains an animatronic, then logic for a jumpscare
    // can occur. Use pointer to easily remove animatronic from door vectors to the pointer.
    Base_Animatronic* office;
    Map map;
    std::string input;
    std::mt19937 rng;
public:
    Game_Night();
    Game_Night(std::mt19937& rng);
    void moveAnimatronic(Base_Animatronic& base);
    void enterOffice(Base_Animatronic& base);
    void playNight();
    void playLiveNight();
};
