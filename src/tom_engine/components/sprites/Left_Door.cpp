#include "Left_Door.h"
#include "../../../graphics/Left_Door_Graphic.h"
#include "iostream"
#define FONT_SIZE 17

// Destructor
Left_Door::~Left_Door() { }

// Default Constructor
Left_Door::Left_Door() {
    left_door_font.loadFromFile("src/graphics/font/CONSOLA.TTF");
    left_door_text.setString(left_door_open_empty_text);
    left_door_text.setFont(left_door_font);
    left_door_text.setCharacterSize(FONT_SIZE);
    left_door_text.setFillColor(sf::Color::White);

    left_door_render_texture.create(100, 325);
    left_door_render_texture.clear(sf::Color::Black);
    left_door_render_texture.draw(left_door_text);
    left_door_render_texture.display();

    left_door_sprite.setTexture(left_door_render_texture.getTexture());
    left_door_sprite.setPosition(sf::Vector2f(97.f, 236.f));
}

// Get Sprite, should change sprite as needed before being drawn to game window
sf::Sprite& Left_Door::getSprite() {
    // texture is redone depending on bool doorClosed changes
    left_door_render_texture.clear(sf::Color::Black);
    left_door_render_texture.draw(left_door_text);
    left_door_render_texture.display();
    // sprite texture is reset
    left_door_sprite.setTexture(left_door_render_texture.getTexture());
    left_door_sprite.setPosition(sf::Vector2f(97.f, 236.f));
    return left_door_sprite;
}

// clickedOn Function (will prob reuse for all sprites)
bool Left_Door::clickedOn(sf::Vector2f &mouse_pos) {
    if (left_door_sprite.getGlobalBounds().contains(mouse_pos)) {
        return true;
    }
    return false;
}

// toggle door function, will def reuse for right door
void Left_Door::openCloseDoor(const bool doorClosed, const bool lightsOn) {
    if (doorClosed) {
        left_door_text.setString(left_door_closed_text);
    }
    else {
        if (lightsOn) {
            left_door_text.setString(left_door_lights_on_text);
        }
        else {
            left_door_text.setString(left_door_open_empty_text);
        }
    }
}

// update door lights based on state of door
void Left_Door::updateLights(const bool lightsOn) {
    if (lightsOn) {
        left_door_text.setString(left_door_lights_on_text);
    }
    else {
        left_door_text.setString(left_door_open_empty_text);
    }
}
