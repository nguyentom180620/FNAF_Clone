#include "Right_Door.h"
#include "../../../graphics/Right_Door_Graphic.h"
#define FONT_SIZE 17

// Destructor
Right_Door::~Right_Door() { }

// Default Constructor
Right_Door::Right_Door() {
    right_door_position = sf::Vector2f(810.f, 236.f);
    door_button_position = sf::Vector2f(915.f, 256.f);
    light_button_position = sf::Vector2f(915.f, 386.f);
    door_button_caption_position = sf::Vector2f(923.f, 346.f);
    light_button_caption_position = sf::Vector2f(920.f, 476.f);

    right_door_font.loadFromFile("src/graphics/font/CONSOLA.TTF");
    right_door_text.setString(right_door_open_empty_text);
    right_door_text.setFont(right_door_font);
    right_door_text.setCharacterSize(FONT_SIZE);
    right_door_text.setFillColor(sf::Color::White);

    right_door_render_texture.create(100, 325);
    right_door_render_texture.clear(sf::Color::Transparent);
    right_door_render_texture.draw(right_door_text);
    right_door_render_texture.display();

    right_door_sprite.setTexture(right_door_render_texture.getTexture());
    right_door_sprite.setPosition(right_door_position);

    door_button_text.setString(right_door_light_button_off_text);
    door_button_text.setFont(right_door_font);
    door_button_text.setCharacterSize(FONT_SIZE);
    door_button_text.setFillColor(sf::Color::White);
    door_button_render_texture.create(100, 100);
    door_button_render_texture.clear(sf::Color::Transparent);
    door_button_render_texture.draw(door_button_text);
    door_button_render_texture.display();
    door_button_sprite.setTexture(door_button_render_texture.getTexture());
    door_button_sprite.setPosition(door_button_position);

    light_button_text.setString(right_door_light_button_off_text);
    light_button_text.setFont(right_door_font);
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
sf::Sprite& Right_Door::getSprite() {
    // texture is redone depending on bool doorClosed changes
    right_door_render_texture.clear(sf::Color::Transparent);
    right_door_render_texture.draw(right_door_text);
    right_door_render_texture.display();
    // sprite texture is reset
    right_door_sprite.setTexture(right_door_render_texture.getTexture());
    right_door_sprite.setPosition(right_door_position);
    return right_door_sprite;
}

sf::Sprite& Right_Door::getDoorButtonSprite() {
    door_button_render_texture.clear(sf::Color::Transparent);
    door_button_render_texture.draw(door_button_text);
    door_button_render_texture.display();
    door_button_sprite.setTexture(door_button_render_texture.getTexture());
    door_button_sprite.setPosition(door_button_position);
    return door_button_sprite;
}

sf::Sprite& Right_Door::getLightButtonSprite() {
    light_button_render_texture.clear(sf::Color::Transparent);
    light_button_render_texture.draw(light_button_text);
    light_button_render_texture.display();
    light_button_sprite.setTexture(light_button_render_texture.getTexture());
    light_button_sprite.setPosition(light_button_position);
    return light_button_sprite;
}

sf::Text& Right_Door::getLightButtonText() {
    return light_button_text;
}

sf::Text& Right_Door::getDoorButtonCaption() {
    return door_button_caption_text;
}

sf::Text& Right_Door::getLightButtonCaption() {
    return light_button_caption_text;
}

// clickedOn Function (will prob reuse for all sprites)
bool Right_Door::clickedOn(sf::Vector2f &mouse_pos) {
    if (right_door_sprite.getGlobalBounds().contains(mouse_pos) or
        door_button_sprite.getGlobalBounds().contains(mouse_pos)) {
        return true;
    }
    return false;
}

// toggle door function, will def reuse for right door
void Right_Door::openCloseDoor(const bool doorClosed, const bool lightsOn) {
    if (doorClosed) {
        right_door_text.setString(right_door_closed_text);
        door_button_text.setString(right_door_light_button_on_text);
    }
    else {
        if (lightsOn) {
            right_door_text.setString(right_door_lights_on_text);
            door_button_text.setString(right_door_light_button_off_text);
        }
        else {
            right_door_text.setString(right_door_open_empty_text);
            door_button_text.setString(right_door_light_button_off_text);
        }
    }
}

// update door lights based on state of door
void Right_Door::doorLightOn() {
    right_door_text.setString(right_door_lights_on_text);
}

void Right_Door::doorLightOff() {
    right_door_text.setString(right_door_open_empty_text);
}

void Right_Door::lightButtonOn() {
    getLightButtonText().setString(right_door_light_button_on_text);
}

void Right_Door::lightButtonOff() {
    getLightButtonText().setString(right_door_light_button_off_text);
}
