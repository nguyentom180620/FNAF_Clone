#include <fstream>
#include "tom_engine/game/Main_Game_Window/Main_Game_Window.h"
// Note: snake_case for variable names, camelCase for functions

// random number generator:
// Reference: https://stackoverflow.com/questions/29549873/stdmt19937-doesnt-return-random-number
static std::random_device rd;
static std::mt19937 rng{rd()};

// Time to make the title screen and connect multiple nights together!
class Home_Screen_Window {
    sf::RenderWindow home_screen {};
    sf::Vector2f translated_mouse_pos;
    sf::Image icon;

    sf::Texture freddy_texture;
    sf::Sprite freddy_sprite;

    sf::Font text_font;

    sf::Text title_text;
    sf::RenderTexture title_render_texture;
    sf::Sprite title_sprite;

    sf::Texture stars_texture;
    sf::Sprite stars_sprite;
    int stars;

    sf::Text select_game_text;
    sf::RenderTexture select_game_render_texture;
    sf::Sprite select_game_sprite;

    sf::Text start_game_text;
    sf::RenderTexture start_game_render_texture;
    sf::Sprite start_game_sprite;

    sf::Text continue_game_text;
    sf::RenderTexture continue_game_render_texture;
    sf::Sprite continue_game_sprite;

    sf::Text continue_night_number_text;
    sf::RenderTexture continue_night_number_render_texture;
    sf::Sprite continue_night_number_sprite;
    int night_number;

    sf::Text sixth_night_game_text;
    sf::RenderTexture sixth_night_render_texture;
    sf::Sprite sixth_night_game_sprite;

    sf::Text custom_night_game_text;
    sf::RenderTexture custom_night_render_texture;
    sf::Sprite custom_night_game_sprite;

    sf::SoundBuffer select_sound_buffer;
    sf::Sound select_sound;
    bool select_sound_playing;

    sf::Music home_screen_music;

    std::string selected_night;
public:
    Home_Screen_Window(int night_number, int stars);
    void Update();
    void Draw();
    std::string Run();
};

int main() {
    bool quit = false;

    while (!quit) {
        // Fstream to FNASCII Player Data
        // First line is what night player will continue from (1-5)
        // Second line is how many stars they earned (3 stars for 100%)
        std::fstream fnascii_fstream("src/savefiles/fnascii_player_data.txt");
        std::string night_to_continue;
        getline(fnascii_fstream, night_to_continue);
        std::cout << "Night to continue from: " << night_to_continue << std::endl;

        std::string stars_earned;
        getline(fnascii_fstream, stars_earned);
        std::cout << "Stars earned: " << stars_earned << std::endl;

        Home_Screen_Window home_screen(std::stoi(night_to_continue), std::stoi(stars_earned));
        std::string selected_night = home_screen.Run();

        std::cout << "Selected Night: " << selected_night << std::endl;

        fnascii_fstream.close();

        if (selected_night == "None") {
            quit = true;
        }
        if (selected_night == "Start Game") {
            fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                                std::fstream::out | std::fstream::trunc);
            night_to_continue = "1";
            fnascii_fstream << night_to_continue << std::endl << stars_earned;
            fnascii_fstream.close();

            // Continue the game until the player dies
            // Update save each night

            // Night 1
            Main_Game_Window night_1(rng, 1, 3, 2, 2, 0);
            bool player_alive = night_1.Run();

            // Night 2
            if (player_alive) {
                fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                                    std::fstream::out | std::fstream::trunc);
                night_to_continue = "2";
                fnascii_fstream << night_to_continue << std::endl << stars_earned;
                fnascii_fstream.close();

                Main_Game_Window night_2(rng, 2, 6, 3, 3, 0);
                player_alive = night_2.Run();
            }

            // Night 3
            if (player_alive) {
                fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                                    std::fstream::out | std::fstream::trunc);
                night_to_continue = "3";
                fnascii_fstream << night_to_continue << std::endl << stars_earned;
                fnascii_fstream.close();

                Main_Game_Window night_3(rng, 3, 3, 4, 7, 1);
                player_alive = night_3.Run();
            }

            // Night 4
            if (player_alive) {
                fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                    std::fstream::out | std::fstream::trunc);
                night_to_continue = "4";
                fnascii_fstream << night_to_continue << std::endl << stars_earned;
                fnascii_fstream.close();

                Main_Game_Window night_4(rng, 4, 5, 8, 6, 2);
                player_alive = night_4.Run();
            }

            // Night 5
            if (player_alive) {
                fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                    std::fstream::out | std::fstream::trunc);
                night_to_continue = "5";
                fnascii_fstream << night_to_continue << std::endl << stars_earned;
                fnascii_fstream.close();

                Main_Game_Window night_5(rng, 5, 8, 7, 9, 3);
                player_alive = night_5.Run();
            }

            // If player finishes night 5, then play credits!
            // Also give them a star
            if (player_alive) {
                fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                    std::fstream::out | std::fstream::trunc);
                if (std::stoi(stars_earned) < 1) {
                    stars_earned = "1";
                }
                fnascii_fstream << night_to_continue << std::endl << stars_earned;
                fnascii_fstream.close();
                // To do credits
            }
        }

        if (selected_night == "Continue Game") {
            // Continue the game until the player dies
            // Update save each night

            bool player_alive = true;
            int continue_num = std::stoi(night_to_continue);

            // Night 1
            if (player_alive && continue_num == 1) {
                Main_Game_Window night_1(rng, 1, 3, 2, 2, 0);
                player_alive = night_1.Run();

                if (player_alive) {
                    fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                    std::fstream::out | std::fstream::trunc);
                    night_to_continue = "2";
                    fnascii_fstream << night_to_continue << std::endl << stars_earned;
                    fnascii_fstream.close();
                    continue_num = std::stoi(night_to_continue);
                }
            }

            // Night 2
            if (player_alive && continue_num == 2) {
                Main_Game_Window night_2(rng, 2, 6, 3, 3, 0);
                player_alive = night_2.Run();

                if (player_alive) {
                    fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                    std::fstream::out | std::fstream::trunc);
                    night_to_continue = "3";
                    fnascii_fstream << night_to_continue << std::endl << stars_earned;
                    fnascii_fstream.close();
                    continue_num = std::stoi(night_to_continue);
                }
            }

            // Night 3
            if (player_alive && continue_num == 3) {
                fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                                    std::fstream::out | std::fstream::trunc);
                night_to_continue = "3";
                fnascii_fstream << night_to_continue << std::endl << stars_earned;
                fnascii_fstream.close();

                Main_Game_Window night_3(rng, 3, 3, 4, 7, 1);
                player_alive = night_3.Run();

                if (player_alive) {
                    fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                        std::fstream::out | std::fstream::trunc);
                    night_to_continue = "4";
                    fnascii_fstream << night_to_continue << std::endl << stars_earned;
                    fnascii_fstream.close();
                    continue_num = std::stoi(night_to_continue);
                }
            }

            // Night 4
            if (player_alive && continue_num == 4) {
                Main_Game_Window night_4(rng, 4, 5, 8, 6, 2);
                player_alive = night_4.Run();

                if (player_alive) {
                    fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                        std::fstream::out | std::fstream::trunc);
                    night_to_continue = "5";
                    fnascii_fstream << night_to_continue << std::endl << stars_earned;
                    fnascii_fstream.close();
                    continue_num = std::stoi(night_to_continue);
                }
            }

            // Night 5
            if (player_alive && continue_num == 5) {
                Main_Game_Window night_5(rng, 5, 8, 7, 9, 3);
                player_alive = night_5.Run();
            }

            // If player finishes night 5, then play credits!
            // Also give them a star
            if (player_alive && continue_num == 5) {
                fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                    std::fstream::out | std::fstream::trunc);
                if (std::stoi(stars_earned) < 1) {
                    stars_earned = "1";
                }
                fnascii_fstream << night_to_continue << std::endl << stars_earned;
                fnascii_fstream.close();
                // To do credits
            }
        }

    }

    return 0;
}

Home_Screen_Window::Home_Screen_Window(int night_number, int stars) {
    home_screen.close();
    home_screen.create(sf::VideoMode(1000, 900), "FNASCII", sf::Style::Close);
    home_screen.setFramerateLimit(60);
    auto mouse_pos = sf::Mouse::getPosition(home_screen);
    translated_mouse_pos = home_screen.mapPixelToCoords(mouse_pos);

    icon.loadFromFile("src/graphics/Freddy_Face.png");
    home_screen.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    freddy_texture.loadFromFile("src/graphics/Freddy_On_Cam.png");
    freddy_sprite.setTexture(freddy_texture);
    freddy_sprite.setPosition(sf::Vector2f(550, 100));
    freddy_sprite.setScale(sf::Vector2f(1.5, 1.5));

    text_font.loadFromFile("src/graphics/font/PixeloidSans.ttf");

    title_text.setFont(text_font);
    title_text.setString("FNASCII");
    title_text.setCharacterSize(125);
    title_text.setFillColor(sf::Color::White);
    title_render_texture.create(title_text.getLocalBounds().width, title_text.getLocalBounds().height+75);
    title_render_texture.clear(sf::Color::Transparent);
    title_render_texture.draw(title_text);
    title_render_texture.display();
    title_sprite.setTexture(title_render_texture.getTexture());
    title_sprite.setPosition(40, 40);

    stars_texture.loadFromFile("src/graphics/white_star.png");
    stars_sprite.setTexture(stars_texture);
    stars_sprite.setScale(sf::Vector2f(0.5, 0.5));
    this->stars = stars;

    select_game_text.setFont(text_font);
    select_game_text.setString(">");
    select_game_text.setCharacterSize(35);
    select_game_text.setFillColor(sf::Color::White);
    select_game_render_texture.create(select_game_text.getLocalBounds().width, select_game_text.getLocalBounds().height+10);
    select_game_render_texture.clear(sf::Color::Transparent);
    select_game_render_texture.draw(select_game_text);
    select_game_render_texture.display();
    select_game_sprite.setTexture(select_game_render_texture.getTexture());
    select_game_sprite.setPosition(80, 500);

    start_game_text.setFont(text_font);
    start_game_text.setString("Start Game");
    start_game_text.setCharacterSize(35);
    start_game_text.setFillColor(sf::Color::White);
    start_game_render_texture.create(start_game_text.getLocalBounds().width, start_game_text.getLocalBounds().height+10);
    start_game_render_texture.clear(sf::Color::Transparent);
    start_game_render_texture.draw(start_game_text);
    start_game_render_texture.display();
    start_game_sprite.setTexture(start_game_render_texture.getTexture());
    start_game_sprite.setPosition(100, 500);

    continue_game_text.setFont(text_font);
    continue_game_text.setString("Continue Game");
    continue_game_text.setCharacterSize(35);
    continue_game_text.setFillColor(sf::Color::White);
    continue_game_render_texture.create(continue_game_text.getLocalBounds().width, continue_game_text.getLocalBounds().height+10);
    continue_game_render_texture.clear(sf::Color::Transparent);
    continue_game_render_texture.draw(continue_game_text);
    continue_game_render_texture.display();
    continue_game_sprite.setTexture(continue_game_render_texture.getTexture());
    continue_game_sprite.setPosition(100, 600);

    this->night_number = night_number;
    continue_night_number_text.setFont(text_font);
    std::string continue_night_number = "Night " + std::to_string(night_number);
    continue_night_number_text.setString(continue_night_number);
    continue_night_number_text.setCharacterSize(30);
    continue_night_number_text.setFillColor(sf::Color::White);
    continue_night_number_render_texture.create(continue_night_number_text.getLocalBounds().width, continue_night_number_text.getLocalBounds().height+10);
    continue_night_number_render_texture.clear(sf::Color::Transparent);
    continue_night_number_render_texture.draw(continue_night_number_text);
    continue_night_number_render_texture.display();
    continue_night_number_sprite.setTexture(continue_night_number_render_texture.getTexture());
    continue_night_number_sprite.setPosition(continue_game_text.getLocalBounds().width + 125, 606);

    sixth_night_game_text.setFont(text_font);
    sixth_night_game_text.setString("6th Night");
    sixth_night_game_text.setCharacterSize(35);
    sixth_night_game_text.setFillColor(sf::Color::White);
    sixth_night_render_texture.create(sixth_night_game_text.getLocalBounds().width, sixth_night_game_text.getLocalBounds().height+10);
    sixth_night_render_texture.clear(sf::Color::Transparent);
    sixth_night_render_texture.draw(sixth_night_game_text);
    sixth_night_render_texture.display();
    sixth_night_game_sprite.setTexture(sixth_night_render_texture.getTexture());
    sixth_night_game_sprite.setPosition(100, 700);

    custom_night_game_text.setFont(text_font);
    custom_night_game_text.setString("Custom Night");
    custom_night_game_text.setCharacterSize(35);
    custom_night_game_text.setFillColor(sf::Color::White);
    custom_night_render_texture.create(custom_night_game_text.getLocalBounds().width, custom_night_game_text.getLocalBounds().height + 10);
    custom_night_render_texture.clear(sf::Color::Transparent);
    custom_night_render_texture.draw(custom_night_game_text);
    custom_night_render_texture.display();
    custom_night_game_sprite.setTexture(custom_night_render_texture.getTexture());
    custom_night_game_sprite.setPosition(100, 800);

    select_sound_buffer.loadFromFile("src/sound/Light_On.wav");
    select_sound.setBuffer(select_sound_buffer);
    select_sound_playing = false;
    select_sound.setVolume(50);

    home_screen_music.openFromFile("src/sound/Fnascii_home_screen.wav");
    home_screen_music.setLoop(true);
    home_screen_music.setVolume(100);
    home_screen_music.play();

    selected_night = "Start Game";
}

void Home_Screen_Window::Update() {
    select_sound_playing = false;
}

void Home_Screen_Window::Draw() {
    home_screen.clear();
    home_screen.draw(freddy_sprite);
    home_screen.draw(title_sprite);
    for (int i = 0; i < stars; i++) {
        stars_sprite.setPosition(40 + i*130, 200);
        home_screen.draw(stars_sprite);
    }
    home_screen.draw(select_game_sprite);
    home_screen.draw(start_game_sprite);
    home_screen.draw(continue_game_sprite);
    home_screen.draw(continue_night_number_sprite);
    home_screen.draw(sixth_night_game_sprite);
    home_screen.draw(custom_night_game_sprite);
    home_screen.display();
}

std::string Home_Screen_Window::Run() {
    while (home_screen.isOpen()) {
        auto mouse_pos = sf::Mouse::getPosition(home_screen);
        translated_mouse_pos = home_screen.mapPixelToCoords(mouse_pos);

        sf::Event event;
        while (home_screen.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                home_screen.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    home_screen.close();
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                if (start_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                    if (selected_night != "Start Game") {
                        if (select_sound_playing == false) {
                            select_sound_playing = true;
                            select_sound.play();
                        }
                        selected_night = "Start Game";
                        select_game_sprite.setPosition(80, 500);
                    }
                }
                if (continue_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                    if (selected_night != "Continue Game") {
                        if (select_sound_playing == false) {
                            select_sound_playing = true;
                            select_sound.play();
                        }
                        selected_night = "Continue Game";
                        select_game_sprite.setPosition(80, 600);
                    }
                }
                if (sixth_night_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                    if (selected_night != "6th Night") {
                        if (select_sound_playing == false) {
                            select_sound_playing = true;
                            select_sound.play();
                        }
                        selected_night = "6th Night";
                        select_game_sprite.setPosition(80, 700);
                    }
                }
                if (custom_night_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                    if (selected_night != "Custom Night") {
                        if (select_sound_playing == false) {
                            select_sound_playing = true;
                            select_sound.play();
                        }
                        selected_night = "Custom Night";
                        select_game_sprite.setPosition(80, 800);
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (start_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        home_screen_music.stop();
                        home_screen.close();
                        return selected_night;
                    }
                    if (continue_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        home_screen_music.stop();
                        home_screen.close();
                        return selected_night;
                    }
                    if (sixth_night_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        home_screen_music.stop();
                        home_screen.close();
                        return selected_night;
                    }
                    if (custom_night_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        home_screen_music.stop();
                        home_screen.close();
                        return selected_night;
                    }
                }
            }
        }
        Update();
        Draw();
    }
    home_screen_music.stop();
    return "None";
}