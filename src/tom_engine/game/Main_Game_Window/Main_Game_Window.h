#pragma once
#include <random>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../../../map/Map.h"
#include "../../game_night_backend/Game_Night_Backend.h"
#include "../../components/sprites/Left_Door.h"
#include  "../../components/sprites/Open_Cam_Button.h"
#include "../../components/sprites/Camera_System.h"
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

    sf::Texture Office_Background_texture;
    sf::Sprite Office_Background_sprite;

    sf::Texture map_layout_texture;
    sf::Sprite map_layout_sprite;

    std::string active_cam;
    Camera_System camera_system;

    sf::Font clock_font;
    sf::Text clock_text;

    bool entered_office;
    bool player_alive;
    bool bonnie_jumpscare;
    int game_time;
    int frame_counter_60;

    bool night_win;
    bool night_lose;

    bool doorClosed;
    bool lightsOn;
    bool left_door_open_close_clicked_on;
    bool left_door_light_clicked_on;
    Left_Door left_door;

    bool open_cam_button_clicked_on;
    bool cam_mode;
    Open_Cam_Button open_cam_button;

    sf::RectangleShape top_line;
    sf::RectangleShape bottom_line;
    sf::RenderWindow game_window {};
    sf::Vector2f translated_mouse_pos;

    sf::RenderTexture freddy_nose;
    sf::Sprite freddy_noseSprite;
    sf::SoundBuffer freddy_sound_buffer;

    sf::SoundBuffer jumpscare_sound_buffer;

    sf::Sound sound_effect;

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
