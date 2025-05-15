#pragma once
#include <SFML/Graphics.hpp>

class Custom_Night_Settings_Window {
    sf::RenderWindow custom_night_screen {};
    sf::Vector2f translated_mouse_pos;
    sf::Image icon;

    int bonnie_level;
    int foxy_level;
    int chica_level;
    int freddy_level;

    sf::Font text_font;

    sf::Text Start_text;
    sf::RenderTexture Start_render_texture;
    sf::Sprite Start_text_sprite;

    sf::Text Freddy_text;
    sf::RenderTexture Freddy_text_render_texture;
    sf::Sprite Freddy_text_sprite;

    sf::Text Freddy_left_text;
    sf::RenderTexture Freddy_left_render_texture;
    sf::Sprite Freddy_left_sprite;

    sf::Text Freddy_right_text;
    sf::RenderTexture Freddy_right_render_texture;
    sf::Sprite Freddy_right_sprite;

    sf::Text Freddy_level_text;
    sf::RenderTexture Freddy_level_render_texture;
    sf::Sprite Freddy_level_sprite;

    sf::Text Foxy_text;
    sf::RenderTexture Foxy_text_render_texture;
    sf::Sprite Foxy_text_sprite;

    sf::Text Foxy_left_text;
    sf::RenderTexture Foxy_left_render_texture;
    sf::Sprite Foxy_left_sprite;

    sf::Text Foxy_right_text;
    sf::RenderTexture Foxy_right_render_texture;
    sf::Sprite Foxy_right_sprite;

    sf::Text Foxy_level_text;
    sf::RenderTexture Foxy_level_render_texture;
    sf::Sprite Foxy_level_sprite;

    sf::Text Bonnie_text;
    sf::RenderTexture Bonnie_text_render_texture;
    sf::Sprite Bonnie_text_sprite;

    sf::Text Bonnie_left_text;
    sf::RenderTexture Bonnie_left_render_texture;
    sf::Sprite Bonnie_left_sprite;

    sf::Text Bonnie_right_text;
    sf::RenderTexture Bonnie_right_render_texture;
    sf::Sprite Bonnie_right_sprite;

    sf::Text Bonnie_level_text;
    sf::RenderTexture Bonnie_level_render_texture;
    sf::Sprite Bonnie_level_sprite;

    sf::Text Chica_text;
    sf::RenderTexture Chica_text_render_texture;
    sf::Sprite Chica_text_sprite;

    sf::Text Chica_left_text;
    sf::RenderTexture Chica_left_render_texture;
    sf::Sprite Chica_left_sprite;

    sf::Text Chica_right_text;
    sf::RenderTexture Chica_right_render_texture;
    sf::Sprite Chica_right_sprite;

    sf::Text Chica_level_text;
    sf::RenderTexture Chica_level_render_texture;
    sf::Sprite Chica_level_sprite;
public:
    Custom_Night_Settings_Window();
    void Update();
    void Draw();
    void Run();
    int getFreddyLevel();
    int getFoxyLevel();
    int getBonnieLevel();
    int getChicaLevel();
};
