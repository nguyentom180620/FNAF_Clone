#pragma once
#include "../Base_Animatronic/Base_Animatronic.h"
#include <SFML/Graphics.hpp>

class Bonnie : public Base_Animatronic {
    sf::Font bonnie_font;
    sf::Text bonnie_text;
    sf::RenderTexture bonnie_render_texture;
    sf::Sprite bonnie_sprite;
public:
    Bonnie(int l, std::string s = "Bonnie");
    sf::Sprite& getSprite();
    void loadAtLeftDoorSprite();
    void resetSprite();
};
