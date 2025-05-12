#pragma once
#include "../Base_Animatronic/Base_Animatronic.h"
#include <SFML/Graphics.hpp>

class Chica : public Base_Animatronic {
    sf::Font chica_font;
    sf::Text chica_text;
    sf::RenderTexture chica_render_texture;
    sf::Sprite chica_sprite;
public:
    Chica(int l, std::string s = "Chica");
    sf::Sprite& getSprite();
    void loadAtRightDoorSprite();
    void resetSprite();
};

