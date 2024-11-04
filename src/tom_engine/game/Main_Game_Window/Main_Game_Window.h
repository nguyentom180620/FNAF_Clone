#pragma once
#include <SFML/Graphics.hpp>
#include "../../components/sprites/Left_Door.h"
class Main_Game_Window {
    bool doorClosed;
    bool left_door_clicked_on;
    Left_Door left_door;
    sf::RenderWindow gameWindow {};
    sf::Vector2f translated_mouse_pos;

    void Update();
    void Draw();
public:
    Main_Game_Window();
    ~Main_Game_Window();
    const bool getdoorClosed();
    void setdoorClosed(bool newBool);
    void Run();
};
