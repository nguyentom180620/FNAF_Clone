#include "Main_Game_Window.h"
#include <iostream>

Main_Game_Window::Main_Game_Window() {
    doorClosed = false;
    left_door_clicked_on = false;
    gameWindow.close();
    gameWindow.create(sf::VideoMode(1000,900), "FNAF Clone", sf::Style::Close);
    gameWindow.setFramerateLimit(60);
    auto mouse_pos = sf::Mouse::getPosition(gameWindow);
    translated_mouse_pos = gameWindow.mapPixelToCoords(mouse_pos);
}

Main_Game_Window::~Main_Game_Window() {}

void Main_Game_Window::Update() {
    // Empty for now, will update as Bonnie and the backend engine is put in

    // Update Left Door
    if (left_door_clicked_on) {
        setdoorClosed(!getdoorClosed());
        left_door.updateDoor(getdoorClosed());
        left_door_clicked_on = false;
    }
}

void Main_Game_Window::Draw() {
    gameWindow.clear();
    gameWindow.draw(left_door.getSprite());
    gameWindow.display();
}

const bool Main_Game_Window::getdoorClosed() {
    return doorClosed;
}

void Main_Game_Window::setdoorClosed(bool newBool) {
    doorClosed = newBool;
}

void Main_Game_Window::Run() {
    while (gameWindow.isOpen()) {
        //     // Mouse pos collection
        auto mouse_pos = sf::Mouse::getPosition(gameWindow);
        translated_mouse_pos = gameWindow.mapPixelToCoords(mouse_pos);

        sf::Event event{};
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    gameWindow.close();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (left_door.clickedOn(translated_mouse_pos)) {
                        left_door_clicked_on = true;
                    }
                }
            }
        }
        Update();
        Draw();
    }
}
