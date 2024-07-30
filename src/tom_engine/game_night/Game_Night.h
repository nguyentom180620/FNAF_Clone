#pragma once
#include "../../map/Map.h"

class Game_Night {
    Map map;
    std::string input;
public:
    Game_Night();
    void moveAnimatronic(Base_Animatronic& base);
    void playNight();
};
