#pragma once
#include "../../map/Map.h"
#include "../../animatronics/Bonnie/Bonnie.h"

class Game_Night {
    Map map;
    std::string input;
public:
    Game_Night();
    void moveAnimatronic(Base_Animatronic& base);
    void playNight();
};
