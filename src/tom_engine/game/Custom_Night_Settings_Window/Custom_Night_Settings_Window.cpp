#include "Custom_Night_Settings_Window.h"

Custom_Night_Settings_Window::Custom_Night_Settings_Window() {
    custom_night_screen.close();
    custom_night_screen.create(sf::VideoMode(500, 360), "FNASCII", sf::Style::Close);
    custom_night_screen.setFramerateLimit(60);
    auto mouse_pos = sf::Mouse::getPosition(custom_night_screen);
    translated_mouse_pos = custom_night_screen.mapPixelToCoords(mouse_pos);

    icon.loadFromFile("src/graphics/Freddy_Face.png");
    custom_night_screen.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    bonnie_level = 0;
    foxy_level = 0;
    chica_level = 0;
    freddy_level = 0;

    text_font.loadFromFile("src/graphics/font/PixeloidSans.ttf");

    Start_text.setFont(text_font);
    Start_text.setString("Start");
    Start_text.setCharacterSize(35);
    Start_text.setFillColor(sf::Color::White);
    Start_render_texture.create(Start_text.getLocalBounds().width, Start_text.getLocalBounds().height+10);
    Start_render_texture.clear(sf::Color::Transparent);
    Start_render_texture.draw(Start_text);
    Start_render_texture.display();
    Start_text_sprite.setTexture(Start_render_texture.getTexture());
    Start_text_sprite.setPosition(180, 270);


    Freddy_text.setFont(text_font);
    Freddy_text.setString("Freddy");
    Freddy_text.setCharacterSize(35);
    Freddy_text.setFillColor(sf::Color::White);
    Freddy_text_render_texture.create(Freddy_text.getLocalBounds().width, Freddy_text.getLocalBounds().height+10);
    Freddy_text_render_texture.clear(sf::Color::Transparent);
    Freddy_text_render_texture.draw(Freddy_text);
    Freddy_text_render_texture.display();
    Freddy_text_sprite.setTexture(Freddy_text_render_texture.getTexture());
    Freddy_text_sprite.setPosition(75, 95 - 60);

    Freddy_left_text.setFont(text_font);
    Freddy_left_text.setString("<");
    Freddy_left_text.setCharacterSize(50);
    Freddy_left_text.setFillColor(sf::Color::White);
    Freddy_left_render_texture.create(Freddy_left_text.getLocalBounds().width+20, Freddy_left_text.getLocalBounds().height+50);
    Freddy_left_render_texture.clear(sf::Color::Transparent);
    Freddy_left_render_texture.draw(Freddy_left_text);
    Freddy_left_render_texture.display();
    Freddy_left_sprite.setTexture(Freddy_left_render_texture.getTexture());
    Freddy_left_sprite.setPosition(70, 125 - 60);

    Freddy_right_text.setFont(text_font);
    Freddy_right_text.setString(">");
    Freddy_right_text.setCharacterSize(50);
    Freddy_right_text.setFillColor(sf::Color::White);
    Freddy_right_render_texture.create(Freddy_right_text.getLocalBounds().width+20, Freddy_right_text.getLocalBounds().height+50);
    Freddy_right_render_texture.clear(sf::Color::Transparent);
    Freddy_right_render_texture.draw(Freddy_right_text);
    Freddy_right_render_texture.display();
    Freddy_right_sprite.setTexture(Freddy_right_render_texture.getTexture());
    Freddy_right_sprite.setPosition(180, 125 - 60);

    Freddy_level_text.setFont(text_font);
    Freddy_level_text.setString(std::to_string(freddy_level));
    Freddy_level_text.setCharacterSize(35);
    Freddy_level_text.setFillColor(sf::Color::White);
    Freddy_level_render_texture.create(Freddy_level_text.getLocalBounds().width + 50, Freddy_level_text.getLocalBounds().height+10);
    Freddy_level_render_texture.clear(sf::Color::Transparent);
    Freddy_level_render_texture.draw(Freddy_level_text);
    Freddy_level_render_texture.display();
    Freddy_level_sprite.setTexture(Freddy_level_render_texture.getTexture());
    Freddy_level_sprite.setPosition(115, 135 - 60);

    Foxy_text.setFont(text_font);
    Foxy_text.setString("Foxy");
    Foxy_text.setCharacterSize(35);
    Foxy_text.setFillColor(sf::Color::White);
    Foxy_text_render_texture.create(Foxy_text.getLocalBounds().width, Foxy_text.getLocalBounds().height+10);
    Foxy_text_render_texture.clear(sf::Color::Transparent);
    Foxy_text_render_texture.draw(Foxy_text);
    Foxy_text_render_texture.display();
    Foxy_text_sprite.setTexture(Foxy_text_render_texture.getTexture());
    Foxy_text_sprite.setPosition(85 + 200, 95 - 60);

    Foxy_left_text.setFont(text_font);
    Foxy_left_text.setString("<");
    Foxy_left_text.setCharacterSize(50);
    Foxy_left_text.setFillColor(sf::Color::White);
    Foxy_left_render_texture.create(Foxy_left_text.getLocalBounds().width+20, Foxy_left_text.getLocalBounds().height+50);
    Foxy_left_render_texture.clear(sf::Color::Transparent);
    Foxy_left_render_texture.draw(Foxy_left_text);
    Foxy_left_render_texture.display();
    Foxy_left_sprite.setTexture(Foxy_left_render_texture.getTexture());
    Foxy_left_sprite.setPosition(70 + 200, 125 - 60);

    Foxy_right_text.setFont(text_font);
    Foxy_right_text.setString(">");
    Foxy_right_text.setCharacterSize(50);
    Foxy_right_text.setFillColor(sf::Color::White);
    Foxy_right_render_texture.create(Foxy_right_text.getLocalBounds().width+20, Foxy_right_text.getLocalBounds().height+50);
    Foxy_right_render_texture.clear(sf::Color::Transparent);
    Foxy_right_render_texture.draw(Foxy_right_text);
    Foxy_right_render_texture.display();
    Foxy_right_sprite.setTexture(Foxy_right_render_texture.getTexture());
    Foxy_right_sprite.setPosition(180 + 200, 125 - 60);

    Foxy_level_text.setFont(text_font);
    Foxy_level_text.setString(std::to_string(foxy_level));
    Foxy_level_text.setCharacterSize(35);
    Foxy_level_text.setFillColor(sf::Color::White);
    Foxy_level_render_texture.create(Foxy_level_text.getLocalBounds().width + 50, Foxy_level_text.getLocalBounds().height+10);
    Foxy_level_render_texture.clear(sf::Color::Transparent);
    Foxy_level_render_texture.draw(Foxy_level_text);
    Foxy_level_render_texture.display();
    Foxy_level_sprite.setTexture(Foxy_level_render_texture.getTexture());
    Foxy_level_sprite.setPosition(115 + 200, 135 - 60);

    Bonnie_text.setFont(text_font);
    Bonnie_text.setString("Bonnie");
    Bonnie_text.setCharacterSize(35);
    Bonnie_text.setFillColor(sf::Color::White);
    Bonnie_text_render_texture.create(Bonnie_text.getLocalBounds().width, Bonnie_text.getLocalBounds().height+10);
    Bonnie_text_render_texture.clear(sf::Color::Transparent);
    Bonnie_text_render_texture.draw(Bonnie_text);
    Bonnie_text_render_texture.display();
    Bonnie_text_sprite.setTexture(Bonnie_text_render_texture.getTexture());
    Bonnie_text_sprite.setPosition(75, 95 + 60);

    Bonnie_left_text.setFont(text_font);
    Bonnie_left_text.setString("<");
    Bonnie_left_text.setCharacterSize(50);
    Bonnie_left_text.setFillColor(sf::Color::White);
    Bonnie_left_render_texture.create(Bonnie_left_text.getLocalBounds().width+20, Bonnie_left_text.getLocalBounds().height+50);
    Bonnie_left_render_texture.clear(sf::Color::Transparent);
    Bonnie_left_render_texture.draw(Bonnie_left_text);
    Bonnie_left_render_texture.display();
    Bonnie_left_sprite.setTexture(Bonnie_left_render_texture.getTexture());
    Bonnie_left_sprite.setPosition(70, 125 + 60);

    Bonnie_right_text.setFont(text_font);
    Bonnie_right_text.setString(">");
    Bonnie_right_text.setCharacterSize(50);
    Bonnie_right_text.setFillColor(sf::Color::White);
    Bonnie_right_render_texture.create(Bonnie_right_text.getLocalBounds().width+20, Bonnie_right_text.getLocalBounds().height+50);
    Bonnie_right_render_texture.clear(sf::Color::Transparent);
    Bonnie_right_render_texture.draw(Bonnie_right_text);
    Bonnie_right_render_texture.display();
    Bonnie_right_sprite.setTexture(Bonnie_right_render_texture.getTexture());
    Bonnie_right_sprite.setPosition(180, 125 + 60);

    Bonnie_level_text.setFont(text_font);
    Bonnie_level_text.setString(std::to_string(bonnie_level));
    Bonnie_level_text.setCharacterSize(35);
    Bonnie_level_text.setFillColor(sf::Color::White);
    Bonnie_level_render_texture.create(Bonnie_level_text.getLocalBounds().width + 50, Bonnie_level_text.getLocalBounds().height+10);
    Bonnie_level_render_texture.clear(sf::Color::Transparent);
    Bonnie_level_render_texture.draw(Bonnie_level_text);
    Bonnie_level_render_texture.display();
    Bonnie_level_sprite.setTexture(Bonnie_level_render_texture.getTexture());
    Bonnie_level_sprite.setPosition(115, 135 + 60);

    Chica_text.setFont(text_font);
    Chica_text.setString("Chica");
    Chica_text.setCharacterSize(35);
    Chica_text.setFillColor(sf::Color::White);
    Chica_text_render_texture.create(Chica_text.getLocalBounds().width, Chica_text.getLocalBounds().height+10);
    Chica_text_render_texture.clear(sf::Color::Transparent);
    Chica_text_render_texture.draw(Chica_text);
    Chica_text_render_texture.display();
    Chica_text_sprite.setTexture(Chica_text_render_texture.getTexture());
    Chica_text_sprite.setPosition(80 + 200, 95 + 60);

    Chica_left_text.setFont(text_font);
    Chica_left_text.setString("<");
    Chica_left_text.setCharacterSize(50);
    Chica_left_text.setFillColor(sf::Color::White);
    Chica_left_render_texture.create(Chica_left_text.getLocalBounds().width+20, Chica_left_text.getLocalBounds().height+50);
    Chica_left_render_texture.clear(sf::Color::Transparent);
    Chica_left_render_texture.draw(Chica_left_text);
    Chica_left_render_texture.display();
    Chica_left_sprite.setTexture(Chica_left_render_texture.getTexture());
    Chica_left_sprite.setPosition(70 + 200, 125 + 60);

    Chica_right_text.setFont(text_font);
    Chica_right_text.setString(">");
    Chica_right_text.setCharacterSize(50);
    Chica_right_text.setFillColor(sf::Color::White);
    Chica_right_render_texture.create(Chica_right_text.getLocalBounds().width+20, Chica_right_text.getLocalBounds().height+50);
    Chica_right_render_texture.clear(sf::Color::Transparent);
    Chica_right_render_texture.draw(Chica_right_text);
    Chica_right_render_texture.display();
    Chica_right_sprite.setTexture(Chica_right_render_texture.getTexture());
    Chica_right_sprite.setPosition(180 + 200, 125 + 60);

    Chica_level_text.setFont(text_font);
    Chica_level_text.setString(std::to_string(chica_level));
    Chica_level_text.setCharacterSize(35);
    Chica_level_text.setFillColor(sf::Color::White);
    Chica_level_render_texture.create(Chica_level_text.getLocalBounds().width + 50, Chica_level_text.getLocalBounds().height+10);
    Chica_level_render_texture.clear(sf::Color::Transparent);
    Chica_level_render_texture.draw(Chica_level_text);
    Chica_level_render_texture.display();
    Chica_level_sprite.setTexture(Chica_level_render_texture.getTexture());
    Chica_level_sprite.setPosition(115 + 200, 135 + 60);
}

void Custom_Night_Settings_Window::Update() {
    Freddy_level_text.setString(std::to_string(freddy_level));
    Freddy_level_render_texture.create(Freddy_level_text.getLocalBounds().width + 50, Freddy_level_text.getLocalBounds().height+10);
    Freddy_level_render_texture.clear(sf::Color::Transparent);
    Freddy_level_render_texture.draw(Freddy_level_text);
    Freddy_level_render_texture.display();
    Freddy_level_sprite.setTexture(Freddy_level_render_texture.getTexture());

    Foxy_level_text.setString(std::to_string(foxy_level));
    Foxy_level_render_texture.create(Foxy_level_text.getLocalBounds().width + 50, Foxy_level_text.getLocalBounds().height+10);
    Foxy_level_render_texture.clear(sf::Color::Transparent);
    Foxy_level_render_texture.draw(Foxy_level_text);
    Foxy_level_render_texture.display();
    Foxy_level_sprite.setTexture(Foxy_level_render_texture.getTexture());

    Bonnie_level_text.setString(std::to_string(bonnie_level));
    Bonnie_level_render_texture.create(Bonnie_level_text.getLocalBounds().width + 50, Bonnie_level_text.getLocalBounds().height+10);
    Bonnie_level_render_texture.clear(sf::Color::Transparent);
    Bonnie_level_render_texture.draw(Bonnie_level_text);
    Bonnie_level_render_texture.display();
    Bonnie_level_sprite.setTexture(Bonnie_level_render_texture.getTexture());

    Chica_level_text.setString(std::to_string(chica_level));
    Chica_level_render_texture.create(Chica_level_text.getLocalBounds().width + 50, Chica_level_text.getLocalBounds().height+10);
    Chica_level_render_texture.clear(sf::Color::Transparent);
    Chica_level_render_texture.draw(Chica_level_text);
    Chica_level_render_texture.display();
    Chica_level_sprite.setTexture(Chica_level_render_texture.getTexture());
}

void Custom_Night_Settings_Window::Draw() {
    custom_night_screen.clear();
    custom_night_screen.draw(Freddy_text_sprite);
    custom_night_screen.draw(Freddy_left_sprite);
    custom_night_screen.draw(Freddy_right_sprite);
    custom_night_screen.draw(Freddy_level_sprite);
    custom_night_screen.draw(Foxy_text_sprite);
    custom_night_screen.draw(Foxy_left_sprite);
    custom_night_screen.draw(Foxy_right_sprite);
    custom_night_screen.draw(Foxy_level_sprite);
    custom_night_screen.draw(Bonnie_text_sprite);
    custom_night_screen.draw(Bonnie_left_sprite);
    custom_night_screen.draw(Bonnie_right_sprite);
    custom_night_screen.draw(Bonnie_level_sprite);
    custom_night_screen.draw(Chica_text_sprite);
    custom_night_screen.draw(Chica_left_sprite);
    custom_night_screen.draw(Chica_right_sprite);
    custom_night_screen.draw(Chica_level_sprite);
    custom_night_screen.draw(Start_text_sprite);
    custom_night_screen.display();
}

void Custom_Night_Settings_Window::Run() {
    while (custom_night_screen.isOpen()) {
        auto mouse_pos = sf::Mouse::getPosition(custom_night_screen);
        translated_mouse_pos = custom_night_screen.mapPixelToCoords(mouse_pos);

        sf::Event event;
        while (custom_night_screen.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                custom_night_screen.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    custom_night_screen.close();
                }
            }
            static bool lock_click;
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left && lock_click != true) {
                    if (Start_text_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        custom_night_screen.close();
                    }
                    if (Freddy_left_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        if (freddy_level > 0) {
                            freddy_level -= 1;
                        }
                    }
                    if (Freddy_right_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        if (freddy_level < 20) {
                            freddy_level += 1;
                        }
                    }
                    if (Foxy_left_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        if (foxy_level > 0) {
                            foxy_level -= 1;
                        }
                    }
                    if (Foxy_right_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        if (foxy_level < 20) {
                            foxy_level += 1;
                        }
                    }
                    if (Bonnie_left_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        if (bonnie_level > 0) {
                            bonnie_level -= 1;
                        }
                    }
                    if (Bonnie_right_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        if (bonnie_level < 20) {
                            bonnie_level += 1;
                        }
                    }
                    if (Chica_left_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        if (chica_level > 0) {
                            chica_level -= 1;
                        }
                    }
                    if (Chica_right_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        if (chica_level < 20) {
                            chica_level += 1;
                        }
                    }
                    lock_click = true;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    lock_click = false;
                }
            }
        }
        Update();
        Draw();
    }
}

int Custom_Night_Settings_Window::getFreddyLevel() {
    return freddy_level;
}

int Custom_Night_Settings_Window::getFoxyLevel() {
    return foxy_level;
}

int Custom_Night_Settings_Window::getBonnieLevel() {
    return bonnie_level;
}

int Custom_Night_Settings_Window::getChicaLevel() {
    return chica_level;
}
