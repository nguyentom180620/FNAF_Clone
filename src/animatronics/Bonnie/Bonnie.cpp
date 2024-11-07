#include "Bonnie.h"
#include "../../graphics/Bonnie_Graphic.h"
#define FONT_SIZE 6

Bonnie::Bonnie(int l, std::string s) : Base_Animatronic(s, l) {
    // Set path map
    path.addToPath("Cam 1A", "Cam 1B");
    path.addToPath("Cam 1A", "Cam 5");
    path.addToPath("Cam 1B", "Cam 2A");
    path.addToPath("Cam 1B", "Cam 5");
    path.addToPath("Cam 2A", "Cam 2B");
    path.addToPath("Cam 2A", "Cam 3");
    path.addToPath("Cam 2B", "Cam 3");
    path.addToPath("Cam 2B", "Left Door");
    path.addToPath("Cam 3", "Cam 2A");
    path.addToPath("Cam 3", "Left Door");
    path.addToPath("Cam 5", "Cam 1B");
    path.addToPath("Cam 5", "Cam 2A");
    path.addToPath("Left Door", "Cam 1B");

    // Set default sprite
    bonnie_font.loadFromFile("src/graphics/font/CONSOLA.TTF");
    bonnie_text.setString("");
    bonnie_text.setFont(bonnie_font);
    bonnie_text.setCharacterSize(FONT_SIZE);
    bonnie_text.setFillColor(sf::Color::White);

    bonnie_render_texture.create(100, 325);
    bonnie_render_texture.clear(sf::Color::Transparent);
    bonnie_render_texture.draw(bonnie_text, sf::RenderStates(sf::BlendNone));
    bonnie_render_texture.display();

    bonnie_sprite.setTexture(bonnie_render_texture.getTexture());
    bonnie_sprite.setPosition(sf::Vector2f(97.f, 236.f));
}

sf::Sprite &Bonnie::getSprite() {
    bonnie_render_texture.clear(sf::Color::Transparent);
    bonnie_render_texture.draw(bonnie_text, sf::RenderStates(sf::BlendNone));
    bonnie_render_texture.display();

    bonnie_sprite.setTexture(bonnie_render_texture.getTexture());
    bonnie_sprite.setPosition(sf::Vector2f(100.f, 275.f));
    return bonnie_sprite;
}

void Bonnie::loadAtLeftDoorSprite() {
    bonnie_text.setString(bonnie_at_left_door);
}

void Bonnie::resetSprite() {
    bonnie_text.setString("");
}
