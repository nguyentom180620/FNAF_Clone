#pragma once
#include <SFML/Graphics.hpp>
#define FONT_SIZE 17

class Camera {
    sf::Vector2f camera_position;
    sf::Font camera_font;
    sf::Text camera_name;
    sf::RenderTexture camera_render_texture;
    sf::Sprite camera_sprite;
public:
    Camera(std::string camera_name, sf::Vector2f camera_position);
    Camera(const Camera &cam) : camera_position(cam.camera_position), camera_name(cam.camera_name){
        camera_font.loadFromFile("src/graphics/font/PixeloidSans.ttf");
        camera_name.setFont(camera_font);
        camera_name.setCharacterSize(FONT_SIZE);
        camera_name.setFillColor(sf::Color::Black);
        camera_name.setPosition(7, 7);

        camera_render_texture.create(80, 33);
        camera_render_texture.clear(sf::Color::White);
        camera_render_texture.draw(this->camera_name);
        camera_render_texture.display();

        camera_sprite.setTexture(camera_render_texture.getTexture());
        camera_sprite.setPosition(camera_position);
    }
    sf::Text getCameraName();
    sf::Sprite& getCameraSprite();
    Camera& operator=(const Camera &cam) {
        return *this;
    }
    bool clickedOn(sf::Vector2f& mouse_pos);
};
