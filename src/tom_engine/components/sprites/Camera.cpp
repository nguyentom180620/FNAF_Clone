#include "Camera.h"

Camera::Camera(std::string camera_name, sf::Vector2f camera_position) {
    this->camera_position = camera_position;

    camera_font.loadFromFile("src/graphics/font/PixeloidSans.ttf");
    this->camera_name.setString(camera_name);
    this->camera_name.setFont(camera_font);
    this->camera_name.setCharacterSize(FONT_SIZE);
    this->camera_name.setFillColor(sf::Color::Black);

    camera_render_texture.create(80, 33);
    camera_render_texture.clear(sf::Color::White);
    camera_render_texture.draw(this->camera_name);
    camera_render_texture.display();

    camera_sprite.setTexture(camera_render_texture.getTexture());
    camera_sprite.setPosition(camera_position);
}

sf::Text Camera::getCameraName() {
    return camera_name;
}

sf::Sprite& Camera::getCameraSprite() {
    return camera_sprite;
}

bool Camera::clickedOn(sf::Vector2f &mouse_pos) {
    if (camera_sprite.getGlobalBounds().contains(mouse_pos)) {
        return true;
    }
    return false;
}
