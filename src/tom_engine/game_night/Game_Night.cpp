#include "Game_Night.h"

Game_Night::Game_Night() = default;

void Game_Night::moveAnimatronic(Base_Animatronic &base) {
    // Right now, just testing to move base from Cam 1A to Cam 1B
    std::string cam_1A = "Cam 1A";
    std::string cam_1B = "Cam 1B";
    if (map.find(base) == map.accessCam(cam_1A)) {
        map.moveAnimatronic(base, map.accessCam(cam_1A), map.accessCam(cam_1B));
    }
}

void Game_Night::playNight() {
    Bonnie bonnie(1);
    map.addAnimatronic(bonnie);

    int move_count = 0;
    while (true) {
        getline(std::cin, input);
        if (input == "end") {
            break;
        }
        move_count++;
        if (move_count == 5) {
            this->moveAnimatronic(bonnie);
            move_count = 0;
        }

        map.printCamContent(input);
    }
}
