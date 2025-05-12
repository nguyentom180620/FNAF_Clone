#include "Chica.h"
#include "../../graphics/Chica_Graphic.h"
#define FONT_SIZE 7

Chica::Chica(int l, std::string s) : Base_Animatronic(s, l) {
    // Set path map
    path.addToPath("Cam 1A", "Cam 1B");
    path.addToPath("Cam 1B", "Cam 6");
    path.addToPath("Cam 1B", "Cam 7");
    path.addToPath("Cam 4A", "Cam 1B");
    path.addToPath("Cam 4A", "Cam 4B");
    path.addToPath("Cam 4B", "Cam 4A");
    path.addToPath("Cam 4B", "Right Door");
    path.addToPath("Cam 6", "Cam 4A");
    path.addToPath("Cam 6", "Cam 7");
    path.addToPath("Cam 7", "Cam 4A");
    path.addToPath("Cam 7", "Cam 6");
    path.addToPath("Right Door", "Cam 4A");

    // Set default sprite
    chica_font.loadFromFile("src/graphics/font/CONSOLA.TTF");
    chica_text.setString("");
    chica_text.setFont(chica_font);
    chica_text.setCharacterSize(FONT_SIZE);
    chica_text.setFillColor(sf::Color::White);

    chica_render_texture.create(100, 325);
    chica_render_texture.clear(sf::Color::Transparent);
    chica_render_texture.draw(chica_text, sf::RenderStates(sf::BlendNone));
    chica_render_texture.display();

    chica_sprite.setTexture(chica_render_texture.getTexture());
    chica_sprite.setPosition(sf::Vector2f(810.f, 315.f));
}

sf::Sprite &Chica::getSprite() {
    chica_render_texture.clear(sf::Color::Transparent);
    chica_render_texture.draw(chica_text, sf::RenderStates(sf::BlendNone));
    chica_render_texture.display();

    chica_sprite.setTexture(chica_render_texture.getTexture());
    chica_sprite.setPosition(sf::Vector2f(810.f, 315.f));
    return chica_sprite;
}

void Chica::loadAtRightDoorSprite() {
    chica_text.setString(chica_at_right_door);
}

void Chica::resetSprite() {
    chica_text.setString("");
}
