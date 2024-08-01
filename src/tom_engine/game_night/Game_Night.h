#pragma once
#include <random>
#include "../../map/Map.h"
#include "../../animatronics/Bonnie/Bonnie.h"

class Game_Night {
    Map map;
    std::string input;
    std::mt19937 rng;
public:
    Game_Night();
    Game_Night(std::mt19937 rng);
    void moveAnimatronic(Base_Animatronic& base);
    void playNight();
};
