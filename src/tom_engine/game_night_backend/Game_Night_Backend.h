#pragma once
#include <random>
#include "../../map/Map.h"
#include "../../animatronics/Bonnie/Bonnie.h"

// Number of seconds in a night (8 mins and 55 seconds)
constexpr unsigned int GAME_LENGTH = 535;

class Game_Night_Backend {
    // Idea: Have a nullptr for the office. If the pointer contains an animatronic, then logic for a jumpscare
    // can occur. Use pointer to easily remove animatronic from door vectors to the pointer.
    Base_Animatronic* office;
    Map map;
    std::string input;
    std::mt19937 rng;
public:
    Game_Night_Backend();
    Game_Night_Backend(std::mt19937& rng);
    void moveAnimatronic(Base_Animatronic& base);
    void enterOffice(Base_Animatronic& base);
    void playNight();
    void playLiveNight();
    void addAnimatronic(Base_Animatronic& base);
    void findAnimatronic(Base_Animatronic& base);
    bool animatronicAtDoorCheck(Base_Animatronic& base, std::string doorName);
    bool animatronicInOffice();
};
