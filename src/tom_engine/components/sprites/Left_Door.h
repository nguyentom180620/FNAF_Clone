#pragma once
#include <SFML/Graphics.hpp>

class Left_Door {
    sf::Font left_door_font;
    sf::Text left_door_text;
    sf::RenderTexture left_door_render_texture;
    sf::Sprite left_door_sprite;
public:
    Left_Door();
    ~Left_Door();
    sf::Sprite& getSprite();
    bool clickedOn(sf::Vector2f& mouse_pos);
    void openCloseDoor(bool doorClosed, bool lightsOn);
    void updateLights(bool lightsOn);
};
