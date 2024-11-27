#pragma once
#include <random>
#include <SFML/Graphics.hpp>
#include "../../game_night_backend/Game_Night_Backend.h"
#include "../../components/sprites/Left_Door.h"
class Main_Game_Window {
    std::mt19937 rng;

    Game_Night_Backend night_1;
    Bonnie bonnie;

    int move_count;
    int bonnie_jumpscare_counter;

    int battery_power;
    std::string battery_display_value;
    int passive_battery_drain_interval;
    std::vector<bool> battery_power_usage_array;
    int battery_power_usage_value;
    sf::Font battery_caption_font;
    sf::Text battery_caption;

    sf::Font usage_caption_font;
    sf::Text usage_caption;
    sf::RenderTexture usage_bar_texture;
    sf::Sprite usage_bar_sprite;

    sf::Font clock_font;
    sf::Text clock_text;

    bool entered_office;
    bool player_alive;
    int game_time;
    int frame_counter_60;

    bool night_win;
    bool night_lose;

    bool doorClosed;
    bool lightsOn;
    bool left_door_open_close_clicked_on;
    bool left_door_light_clicked_on;
    Left_Door left_door;
    sf::RectangleShape top_line;
    sf::RectangleShape bottom_line;
    sf::RenderWindow game_window {};
    sf::Vector2f translated_mouse_pos;

    void Update();
    void Draw();
public:
    Main_Game_Window(std::mt19937& rng);
    ~Main_Game_Window();
    const bool getdoorClosed();
    void setdoorClosed(bool newBool);
    const bool getLightsOn();
    void setLightsOn(bool newBool);
    void Run();
};
