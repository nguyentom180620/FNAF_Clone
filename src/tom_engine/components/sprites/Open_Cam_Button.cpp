#include "Open_Cam_Button.h"

Open_Cam_Button::Open_Cam_Button() {
    Open_Cam_Button_texture.loadFromFile("src/graphics/fnaf_open_cam_button.png", sf::IntRect({0, 0}, {1024, 195}));
    Open_Cam_Button_sprite.setTexture(Open_Cam_Button_texture);
    Open_Cam_Button_sprite.setPosition(sf::Vector2f(0, 800));
    Open_Cam_Button_sprite.setScale(1, 0.49);
}

Open_Cam_Button::~Open_Cam_Button() {}

sf::Sprite &Open_Cam_Button::getSprite() {
    return Open_Cam_Button_sprite;
}

bool Open_Cam_Button::clickedOn(sf::Vector2f &mouse_pos) {
    if (Open_Cam_Button_sprite.getGlobalBounds().contains(mouse_pos)) {
        return true;
    }
    return false;
}
