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
