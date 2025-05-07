#pragma once
#include <SFML/Graphics.hpp>

class Open_Cam_Button {
    sf::Texture Open_Cam_Button_texture;
    sf::Sprite Open_Cam_Button_sprite;
public:
    Open_Cam_Button();
    ~Open_Cam_Button();
    sf::Sprite& getSprite();
    bool clickedOn(sf::Vector2f& mouse_pos);
};