#include "Main_Game_Window.h"
#include <iostream>

Main_Game_Window::Main_Game_Window(std::mt19937& rng): night_1(rng), bonnie(1) {
    this->rng = rng;

    night_1.addAnimatronic(bonnie);
    move_count = 0;
    bonnie_jumpscare_counter = 0;
    entered_office = false;
    player_alive = true;
    game_time = 0;
    frame_counter_60 = 0;

    night_win = false;
    night_lose = false;

    doorClosed = false;
    lightsOn = false;
    left_door_open_close_clicked_on = false;
    left_door_light_clicked_on = false;
    game_window.close();
    game_window.create(sf::VideoMode(1000, 900), "FNAF Clone", sf::Style::Close);
    game_window.setFramerateLimit(60);
    auto mouse_pos = sf::Mouse::getPosition(game_window);
    translated_mouse_pos = game_window.mapPixelToCoords(mouse_pos);
}

Main_Game_Window::~Main_Game_Window() {}

void Main_Game_Window::Update() {
    // Update Left Door open close toggle
    if (left_door_open_close_clicked_on) {
        setdoorClosed(!getdoorClosed());
        if (doorClosed == true) {
            std::cout << "You closed the door!" << std::endl;
        }
        else {
            std::cout << "You opened the door!" << std::endl;
        }
        left_door.openCloseDoor(getdoorClosed(), getLightsOn());
        left_door_open_close_clicked_on = false;
        // Reset Animatronic Sprite
        bonnie.resetSprite();
    }
    // Update Left Door Light
    if (left_door_light_clicked_on) {
        setLightsOn(true);
        if (doorClosed == false) {
            // // If Bonnie is at the door,
            if (night_1.animatronicAtDoorCheck(bonnie, "Left Door")) {
                bonnie.loadAtLeftDoorSprite();
                setLightsOn(false);
                left_door.updateLights(getLightsOn());
            }
            else {
                left_door.updateLights(getLightsOn());
                // Reset Animatronic Sprites
                bonnie.resetSprite();
            }
        }
        left_door_light_clicked_on = false;
    }

    // Bonnie moviement and timer engine
    ++frame_counter_60;
    if (frame_counter_60 >= 60) {
        if (game_time >= GAME_LENGTH) {
            night_win = true;
        }
        switch (game_time) {
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
            default: break;
        }
        if (night_1.animatronicInOffice()) {
            if (bonnie_jumpscare_counter >= 3) {
                std::cout << "Bonnie Jumpscare!" << std::endl;
                player_alive = false;
                night_lose = true;
            }
            bonnie_jumpscare_counter++;
        }
        if (move_count == 5) {
            if (night_1.animatronicAtDoorCheck(bonnie, "Left Door")) {
                if (getdoorClosed() == false) {
                    night_1.enterOffice(bonnie);
                    entered_office = true;
                }
                else {
                    std::cout << "Bonnie hit the door, he's gone now but broke the door!" << std::endl;
                    setdoorClosed(false);
                    left_door.openCloseDoor(getdoorClosed(), getLightsOn());
                }
            }
            if (entered_office == false) {
                night_1.moveAnimatronic(bonnie);
                night_1.findAnimatronic(bonnie);
            }
            move_count = 0;
        }
        ++move_count;
        ++game_time;
        frame_counter_60 = 0;
    }
}

void Main_Game_Window::Draw() {
    game_window.clear();
    game_window.draw(left_door.getSprite());
    game_window.draw(bonnie.getSprite());
    game_window.display();
}

const bool Main_Game_Window::getdoorClosed() {
    return doorClosed;
}

void Main_Game_Window::setdoorClosed(bool newBool) {
    doorClosed = newBool;
}

const bool Main_Game_Window::getLightsOn() {
    return lightsOn;
}

void Main_Game_Window::setLightsOn(bool newBool) {
    lightsOn = newBool;
}

void Main_Game_Window::Run() {
    while (game_window.isOpen()) {
        if (night_win == true) {
            game_window.close();
        }
        if (night_lose == true) {
            game_window.close();
        }
        //     // Mouse pos collection
        auto mouse_pos = sf::Mouse::getPosition(game_window);
        translated_mouse_pos = game_window.mapPixelToCoords(mouse_pos);

        sf::Event event{};
        while (game_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                game_window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    game_window.close();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (left_door.clickedOn(translated_mouse_pos)) {
                        left_door_open_close_clicked_on = true;
                    }
                }
            }
            // Right click hold on door for light mechanic
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                if (left_door.clickedOn(translated_mouse_pos)) {
                    left_door_light_clicked_on = true;
                }
            }
            // Reference for this idea: https://en.sfml-dev.org/forums/index.php?topic=13412.0
            if (event.type == sf::Event::MouseButtonReleased) {
                // If right clicked released for left door light, stop!
                if (event.mouseButton.button == sf::Mouse::Right) {
                    setLightsOn(false);
                    if (doorClosed == false) {
                        left_door.updateLights(getLightsOn());
                    }
                    // Reset Animatronic Sprites
                    bonnie.resetSprite();
                }
            }
        }
        Update();
        Draw();
    }
    // // print section to test changes to the game state variables
    std::cout << std::endl;
    std::cout << "Move Counter: " << move_count << std::endl;
    std::cout << "Bonnie Jumpscare Counter: " << bonnie_jumpscare_counter << std::endl;
    std::cout << "Entered Office: " << std::boolalpha << entered_office << std::endl;
    std::cout << "Door Closed: " << std::boolalpha << doorClosed << std::endl;
    std::cout << "Player Alive: " << std::boolalpha << player_alive << std::endl;
    std::cout << "Game Time (in seconds): " << game_time << std::endl;
    std::cout << std::endl;

    if (player_alive) {
        std::cout << "6:00 AM! You lived!" << std::endl;
    }
    else {
        std::cout << "You died..." << std::endl;
    }
}
