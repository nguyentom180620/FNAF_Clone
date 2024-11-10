#include "Left_Door.h"
#include "../../../graphics/Left_Door_Graphic.h"
#include "iostream"
#define FONT_SIZE 17

// Destructor
Left_Door::~Left_Door() { }

// Default Constructor
Left_Door::Left_Door() {
    left_door_position = sf::Vector2f(97.f, 236.f);
    door_button_position = sf::Vector2f(20.f, 256.f);
    light_button_position = sf::Vector2f(20.f, 386.f);
    door_button_caption_position = sf::Vector2f(27.f, 346.f);
    light_button_caption_position = sf::Vector2f(24.f, 476.f);

    left_door_font.loadFromFile("src/graphics/font/CONSOLA.TTF");
    left_door_text.setString(left_door_open_empty_text);
    left_door_text.setFont(left_door_font);
    left_door_text.setCharacterSize(FONT_SIZE);
    left_door_text.setFillColor(sf::Color::White);

    left_door_render_texture.create(100, 325);
    left_door_render_texture.clear(sf::Color::Transparent);
    left_door_render_texture.draw(left_door_text);
    left_door_render_texture.display();

    left_door_sprite.setTexture(left_door_render_texture.getTexture());
    left_door_sprite.setPosition(left_door_position);

    door_button_text.setString(door_light_button_off_text);
    door_button_text.setFont(left_door_font);
    door_button_text.setCharacterSize(FONT_SIZE);
    door_button_text.setFillColor(sf::Color::White);
    door_button_render_texture.create(100, 100);
    door_button_render_texture.clear(sf::Color::Transparent);
    door_button_render_texture.draw(door_button_text);
    door_button_render_texture.display();
    door_button_sprite.setTexture(door_button_render_texture.getTexture());
    door_button_sprite.setPosition(door_button_position);

    light_button_text.setString(door_light_button_off_text);
    light_button_text.setFont(left_door_font);
    light_button_text.setCharacterSize(FONT_SIZE);
    light_button_text.setFillColor(sf::Color::White);
    light_button_render_texture.create(100, 100);
    light_button_render_texture.clear(sf::Color::Transparent);
    light_button_render_texture.draw(light_button_text);
    light_button_render_texture.display();
    light_button_sprite.setTexture(light_button_render_texture.getTexture());
    light_button_sprite.setPosition(light_button_position);

    door_light_caption_font.loadFromFile("src/graphics/font/PixeloidSans.ttf");
    door_button_caption_text.setFont(door_light_caption_font);
    door_button_caption_text.setString("DOOR");
    door_button_caption_text.setCharacterSize(FONT_SIZE);
    door_button_caption_text.setFillColor(sf::Color::White);
    door_button_caption_text.setPosition(door_button_caption_position);
    light_button_caption_text.setFont(door_light_caption_font);
    light_button_caption_text.setString("LIGHT");
    light_button_caption_text.setCharacterSize(FONT_SIZE);
    light_button_caption_text.setFillColor(sf::Color::White);
    light_button_caption_text.setPosition(light_button_caption_position);
}

// Get Sprite, should change sprite as needed before being drawn to game window
sf::Sprite& Left_Door::getSprite() {
    // texture is redone depending on bool doorClosed changes
    left_door_render_texture.clear(sf::Color::Transparent);
    left_door_render_texture.draw(left_door_text);
    left_door_render_texture.display();
    // sprite texture is reset
    left_door_sprite.setTexture(left_door_render_texture.getTexture());
    left_door_sprite.setPosition(left_door_position);
    return left_door_sprite;
}

sf::Sprite& Left_Door::getDoorButtonSprite() {
    door_button_render_texture.clear(sf::Color::Transparent);
    door_button_render_texture.draw(door_button_text);
    door_button_render_texture.display();
    door_button_sprite.setTexture(door_button_render_texture.getTexture());
    door_button_sprite.setPosition(door_button_position);
    return door_button_sprite;
}

sf::Sprite& Left_Door::getLightButtonSprite() {
    light_button_render_texture.clear(sf::Color::Transparent);
    light_button_render_texture.draw(light_button_text);
    light_button_render_texture.display();
    light_button_sprite.setTexture(light_button_render_texture.getTexture());
    light_button_sprite.setPosition(light_button_position);
    return light_button_sprite;
}

sf::Text& Left_Door::getLightButtonText() {
    return light_button_text;
}

sf::Text& Left_Door::getDoorButtonCaption() {
    return door_button_caption_text;
}

sf::Text& Left_Door::getLightButtonCaption() {
    return light_button_caption_text;
}

// clickedOn Function (will prob reuse for all sprites)
bool Left_Door::clickedOn(sf::Vector2f &mouse_pos) {
    if (left_door_sprite.getGlobalBounds().contains(mouse_pos) or
        door_button_sprite.getGlobalBounds().contains(mouse_pos)) {
        return true;
    }
    return false;
}

// toggle door function, will def reuse for right door
void Left_Door::openCloseDoor(const bool doorClosed, const bool lightsOn) {
    if (doorClosed) {
        left_door_text.setString(left_door_closed_text);
        door_button_text.setString(door_light_button_on_text);
    }
    else {
        if (lightsOn) {
            left_door_text.setString(left_door_lights_on_text);
            door_button_text.setString(door_light_button_off_text);
        }
        else {
            left_door_text.setString(left_door_open_empty_text);
            door_button_text.setString(door_light_button_off_text);
        }
    }
}

// update door lights based on state of door
void Left_Door::doorLightOn() {
    left_door_text.setString(left_door_lights_on_text);
}

void Left_Door::doorLightOff() {
    left_door_text.setString(left_door_open_empty_text);
}

void Left_Door::lightButtonOn() {
    getLightButtonText().setString(door_light_button_on_text);
}

void Left_Door::lightButtonOff() {
    getLightButtonText().setString(door_light_button_off_text);
}
