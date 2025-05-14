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

    sf::Text select_game_text;
    sf::RenderTexture select_game_render_texture;
    sf::Sprite select_game_sprite;

    sf::Text start_game_text;
    sf::RenderTexture start_game_render_texture;
    sf::Sprite start_game_sprite;

    sf::Text continue_game_text;
    sf::RenderTexture continue_game_render_texture;
    sf::Sprite continue_game_sprite;

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
    Home_Screen_Window();
    void Update();
    void Draw();
    std::string Run();
};

int main() {
    Home_Screen_Window home_screen;
    std::string selected_night = home_screen.Run();

    std::cout << "Selected Night: " << selected_night << std::endl;

    Main_Game_Window main_game_window(rng, 20, 20, 20, 20);
    main_game_window.Run();

    return 0;
}

Home_Screen_Window::Home_Screen_Window() {
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
    // Also write which night to continue from here
    continue_game_text.setCharacterSize(35);
    continue_game_text.setFillColor(sf::Color::White);
    continue_game_render_texture.create(continue_game_text.getLocalBounds().width, continue_game_text.getLocalBounds().height+10);
    continue_game_render_texture.clear(sf::Color::Transparent);
    continue_game_render_texture.draw(continue_game_text);
    continue_game_render_texture.display();
    continue_game_sprite.setTexture(continue_game_render_texture.getTexture());
    continue_game_sprite.setPosition(100, 600);


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
    home_screen.draw(select_game_sprite);
    home_screen.draw(start_game_sprite);
    home_screen.draw(continue_game_sprite);
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