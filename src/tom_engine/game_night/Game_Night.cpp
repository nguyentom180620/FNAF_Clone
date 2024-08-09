#include "Game_Night.h"

Game_Night::Game_Night() = default;

Game_Night::Game_Night(std::mt19937 rng) {
    office = nullptr;
    this->rng = rng;
}

void Game_Night::moveAnimatronic(Base_Animatronic& base) {
    // Generate the two cams the animatronic will move between through random numbers
    const std::string oldCamString = map.find(base).getName();
    const std::vector<std::string> newCamVector = base.getPath().at(oldCamString);
    static std::uniform_int_distribution<> uid(0,newCamVector.size() - 1);
    const unsigned int newCamInt = uid(rng);
    const std::string newCamString = newCamVector[newCamInt];

    // Right now, just testing to move base from Cam 1A to Cam 1B
    std::string oldCam = oldCamString;
    std::string newCam = newCamString;
    if (map.find(base) == map.accessCam(oldCam)) {
        map.moveAnimatronic(base, map.accessCam(oldCam), map.accessCam(newCam));
    }
    else {
        std::cout << "Something went wrong in the Game_Night::moveAnimatronic(Base_Animatronic& base) function!"
        << std::endl;
    }
}

// This function should only be called when animatronics are at a door
void Game_Night::enterOffice(Base_Animatronic &base) {
    std::string door = map.find(base).getName();
    if (map.find(base) == map.accessCam(door)) {
        map.accessCam(door).removeAnimatronic(base);
        office = &base;
        std::cout << "Bonnie entered the office!" << std::endl;
    }
    else {
        std::cout << "Something went wrong in Game_Night::enterOffice (Shouldn't be called right now)" << std::endl;
    }
}

void Game_Night::playNight() {
    Bonnie bonnie(1);
    map.addAnimatronic(bonnie);
    const auto path_veticies = bonnie.getPath();
    for (auto iter = path_veticies.begin(); iter != path_veticies.end(); ++iter) {
        std::cout << iter->first << std::endl;
    }

    int move_count = 0;
    int bonnie_jumpscare_counter = 0;
    bool enteredOffice = false;
    bool doorClosed = false;
    while (true) {
        if (office) {
            if (bonnie_jumpscare_counter >= 3) {
                std::cout << "Bonnie Jumpscare!" << std::endl;
                break;
            }
            bonnie_jumpscare_counter++;
        }
        getline(std::cin, input);
        if (input == "end") {
            break;
        }
        move_count++;
        if (input == "Close Door") {
            std::cout << "You closed the door!" << std::endl;
            doorClosed = true;
            continue;
        }
        if (move_count == 5) {
            if (map.animatronicAtDoor(bonnie, "Left Door")) {
                if (!doorClosed) {
                    enterOffice(bonnie);
                    enteredOffice = true;
                }
                else {
                    std::cout << "Bonnie hit the door, he's gone now but broke the door!" << std::endl;
                    doorClosed = false;
                }
            }
            if (!enteredOffice) {
                moveAnimatronic(bonnie);
            }
            move_count = 0;
        }
        map.printCamContent(input);
    }
}
