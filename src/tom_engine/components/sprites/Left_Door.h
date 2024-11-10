#pragma once
#include <SFML/Graphics.hpp>

class Left_Door {
    sf::Font left_door_font;
    sf::Text left_door_text;
    sf::RenderTexture left_door_render_texture;
    sf::Sprite left_door_sprite;

    sf::Text door_button_text;
    sf::RenderTexture door_button_render_texture;
    sf::Sprite door_button_sprite;
    sf::Text light_button_text;
    sf::RenderTexture light_button_render_texture;
    sf::Sprite light_button_sprite;

    sf::Font door_light_caption_font;
    sf::Text door_button_caption_text;
    sf::Text light_button_caption_text;

    sf::Vector2f left_door_position;
    sf::Vector2f door_button_position;
    sf::Vector2f light_button_position;
    sf::Vector2f door_button_caption_position;
    sf::Vector2f light_button_caption_position;
public:
    Left_Door();
    ~Left_Door();
    sf::Sprite& getSprite();
    sf::Sprite& getDoorButtonSprite();
    sf::Sprite& getLightButtonSprite();
    sf::Text& getLightButtonText();
    sf::Text& getDoorButtonCaption();
    sf::Text& getLightButtonCaption();
    bool clickedOn(sf::Vector2f& mouse_pos);
    void openCloseDoor(bool doorClosed, bool lightsOn);
    void doorLightOn();
    void doorLightOff();
    void lightButtonOn();
    void lightButtonOff();
};
