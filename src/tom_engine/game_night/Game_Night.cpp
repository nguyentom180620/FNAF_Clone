#include "Game_Night.h"

// Number of seconds in a night (8 mins and 55 seconds)
constexpr unsigned int GAME_LENGTH = 535;

Game_Night::Game_Night() = default;

Game_Night::Game_Night(std::mt19937 rng) {
    office = nullptr;
    this->rng = rng;
}

void Game_Night::moveAnimatronic(Base_Animatronic& base) {
    // Generate the two cams the animatronic will move between through random numbers
    const std::string& oldCamString = map.find(base).getName();
    const std::vector<std::string>& newCamVector = base.getPath().at(oldCamString);
    std::uniform_int_distribution<int> uid(0,newCamVector.size() - 1);
    const unsigned int newCamInt = uid(rng);
    const std::string& newCamString = newCamVector[newCamInt];

    // Right now, just testing to move base from Cam 1A to Cam 1B
    if (map.find(base) == map.accessCam(oldCamString)) {
        map.moveAnimatronic(base, map.accessCam(oldCamString), map.accessCam(newCamString));
    }
    else {
        std::cout << "Something went wrong in the Game_Night::moveAnimatronic(Base_Animatronic& base) function!"
        << std::endl;
    }
}

// This function should only be called when animatronics are at a door
void Game_Night::enterOffice(Base_Animatronic &base) {
    const std::string& door = map.find(base).getName();
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

    int move_count = 0;
    int bonnie_jumpscare_counter = 0;
    bool enteredOffice = false;
    bool doorClosed = false;
    bool playerAlive = true;
    int gameTime = 0.0;
    while (true) {
        if (gameTime >= GAME_LENGTH) {
            break;
        }
        switch (gameTime) {
            case 0:
                std::cout << "12 AM" << std::endl;
                break;
            case 90:
                std::cout << "1 AM" << std::endl;
                break;
            case 179:
                std::cout << "2 AM" << std::endl;
                break;
            case 268:
                std::cout << "3 AM" << std::endl;
                break;
            case 357:
                std::cout << "4 AM" << std::endl;
                break;
            case 446:
                std::cout << "5 AM" << std::endl;
                break;
            case GAME_LENGTH:
                std::cout << "6 AM" << std::endl;
                break;
            default: ;
        }
        if (office) {
            if (bonnie_jumpscare_counter >= 3) {
                std::cout << "Bonnie Jumpscare!" << std::endl;
                playerAlive = false;
                break;
            }
            bonnie_jumpscare_counter++;
        }
        getline(std::cin, input);
        if (input == "end") {
            break;
        }
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
        move_count++;
        map.printCamContent(input);
        gameTime += 1;
    }
    if (playerAlive) {
        std::cout << "6:00 AM! You lived!" << std::endl;
    }
    else {
        std::cout << "You died..." << std::endl;
    }
}
