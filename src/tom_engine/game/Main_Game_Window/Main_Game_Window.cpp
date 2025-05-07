#include "Main_Game_Window.h"
#include <iostream>
#define FONT_SIZE 35

Main_Game_Window::Main_Game_Window(std::mt19937& rng): night_1(rng), bonnie(1) {
    this->rng = rng;

    night_1.addAnimatronic(bonnie);
    move_count = 0;
    bonnie_jumpscare_counter = 0;
    battery_power = 1000;
    passive_battery_drain_interval = 1000;
    battery_display_value = battery_power / 10;
    battery_power_usage_array = {true, false, false};
    battery_power_usage_value = std::count(battery_power_usage_array.begin(),
        battery_power_usage_array.end(), true);
    entered_office = false;
    player_alive = true;
    game_time = 0;
    frame_counter_60 = 0;

    night_win = false;
    night_lose = false;

    doorClosed = false;
    lightsOn = false;
    left_door_open_close_clicked_on = false;
    left_door_light_clicked_on = false;

    battery_caption_font.loadFromFile("src/graphics/font/PixeloidSans.ttf");
    battery_caption.setFont(battery_caption_font);
    battery_display_value = std::to_string(battery_power / 10);
    battery_caption.setString("Battery: " + battery_display_value + '%');
    battery_caption.setCharacterSize(FONT_SIZE);
    battery_caption.setFillColor(sf::Color::White);
    battery_caption.setPosition(sf::Vector2f(20, 25));

    usage_caption_font.loadFromFile("src/graphics/font/PixeloidSans.ttf");
    usage_caption.setFont(usage_caption_font);
    usage_caption.setString("Usage:");
    usage_caption.setCharacterSize(FONT_SIZE);
    usage_caption.setFillColor(sf::Color::White);
    usage_caption.setPosition(sf::Vector2f(350, 25));

    usage_bar_texture.create(25, 55);
    usage_bar_texture.clear(sf::Color::White);
    usage_bar_texture.display();
    usage_bar_sprite.setTexture(usage_bar_texture.getTexture());
    usage_bar_sprite.setPosition(sf::Vector2f(485, 21));

    Office_Background_texture.loadFromFile("src/graphics/Fnaf_background_image.png", sf::IntRect({50, 0}, {753, 526}));
    Office_Background_sprite.setTexture(Office_Background_texture);
    Office_Background_sprite.setPosition(200,150);
    Office_Background_sprite.setScale(0.94, 0.94);

    clock_font.loadFromFile("src/graphics/font/PixeloidSans.ttf");
    clock_text.setFont(clock_font);
    clock_text.setString("12 AM, Night 1");
    clock_text.setCharacterSize(FONT_SIZE);
    clock_text.setFillColor(sf::Color::White);
    clock_text.setPosition(sf::Vector2f(700, 25));

    top_line.setFillColor(sf::Color::Transparent);
    top_line.setOutlineColor(sf::Color::White);
    top_line.setSize(sf::Vector2f(1000,0));
    top_line.setPosition(sf::Vector2f(0, 100));
    top_line.setOutlineThickness(1.0f);
    bottom_line.setFillColor(sf::Color::Transparent);
    bottom_line.setOutlineColor(sf::Color::White);
    bottom_line.setSize(sf::Vector2f(1000,0));
    bottom_line.setPosition(sf::Vector2f(0, 800));
    bottom_line.setOutlineThickness(1.0f);

    game_window.close();
    game_window.create(sf::VideoMode(1000, 900), "FNAF Clone", sf::Style::Close);
    game_window.setFramerateLimit(60);
    auto mouse_pos = sf::Mouse::getPosition(game_window);
    translated_mouse_pos = game_window.mapPixelToCoords(mouse_pos);
}

Main_Game_Window::~Main_Game_Window() {}

void Main_Game_Window::Update() {
    // These only work if power is above 0!
    if (battery_power > 0) {
        // Update Left Door open close toggle
        if (left_door_open_close_clicked_on) {
            setdoorClosed(!getdoorClosed());
            if (doorClosed == true) {
                std::cout << "You closed the door!" << std::endl;
            }
            else {
                std::cout << "You opened the door!" << std::endl;
            }
            left_door.openCloseDoor(getdoorClosed(), getLightsOn());
            left_door_open_close_clicked_on = false;
            // Reset Animatronic Sprite
            bonnie.resetSprite();
        }
        // Update Left Door Light
        if (left_door_light_clicked_on) {
            setLightsOn(true);
            left_door_light_clicked_on = false;
        }
    }
    else {
        doorClosed = false;
        lightsOn = false;
        battery_power_usage_array = {false, false, false};
        left_door.doorLightOff();
        left_door.lightButtonOff();
        left_door.openCloseDoor(doorClosed, lightsOn);
    }

    // Have Left Door update while lightsOn is true
    // Not going to lie, set up is pretty shitty with disconnect between clicking and updating lights, but it works!
    if (lightsOn) {
        left_door.lightButtonOn();
        if (doorClosed == false) {
            // // If Bonnie is at the door,
            if (night_1.animatronicAtDoorCheck(bonnie, "Left Door")) {
                bonnie.loadAtLeftDoorSprite();
                left_door.doorLightOff();
            }
            else {
                // Reset Animatronic Sprites
                bonnie.resetSprite();
                left_door.doorLightOn();
            }
        }
    }
    else {
        if (doorClosed == false) {
            left_door.doorLightOff();
        }
        left_door.lightButtonOff();
        bonnie.resetSprite();
    }

    // Update array every frame to get faster feedback on usage bar
    if (doorClosed) {
        battery_power_usage_array[1] = true;
    }
    else {
        battery_power_usage_array[1] = false;
    }
    if (lightsOn) {
        battery_power_usage_array[2] = true;
    }
    else {
        battery_power_usage_array[2] = false;
    }
    battery_power_usage_value = std::count(battery_power_usage_array.begin(),
        battery_power_usage_array.end(), true);

    // Timer engine
    // Manages Bonnie and Battery
    ++frame_counter_60;
    if (frame_counter_60 >= 60) {
        if (game_time >= GAME_LENGTH) {
            night_win = true;
        }
        switch (game_time) {
            case 0:
                std::cout << "12 AM" << std::endl;
            break;
            case 90:
                clock_text.setString("1 AM, Night 1");
                std::cout << "1 AM" << std::endl;
            break;
            case 179:
                clock_text.setString("2 AM, Night 1");
                std::cout << "2 AM" << std::endl;
            break;
            case 268:
                clock_text.setString("3 AM, Night 1");
                std::cout << "3 AM" << std::endl;
            break;
            case 357:
                clock_text.setString("4 AM, Night 1");
                std::cout << "4 AM" << std::endl;
            break;
            case 446:
                clock_text.setString("5 AM, Night 1");
                std::cout << "5 AM" << std::endl;
            break;
            case GAME_LENGTH:
                clock_text.setString("6 AM, Night 1");
                std::cout << "6 AM" << std::endl;
            break;
            default: break;
        }
        if (night_1.animatronicInOffice()) {
            if (bonnie_jumpscare_counter >= 3) {
                std::cout << "Bonnie Jumpscare!" << std::endl;
                player_alive = false;
                night_lose = true;
            }
            bonnie_jumpscare_counter++;
        }
        if (move_count == 5) {
            if (night_1.animatronicAtDoorCheck(bonnie, "Left Door")) {
                if (getdoorClosed() == false) {
                    night_1.enterOffice(bonnie);
                    entered_office = true;
                }
                else {
                    std::cout << "Bonnie hit the door, he's gone now but broke the door!" << std::endl;
                    setdoorClosed(false);
                    left_door.openCloseDoor(getdoorClosed(), getLightsOn());
                }
            }
            if (entered_office == false) {
                night_1.moveAnimatronic(bonnie);
                night_1.findAnimatronic(bonnie);
            }
            move_count = 0;
        }
        // Passive Battery Drain and Usage Drain
        if (game_time % passive_battery_drain_interval == 0) {
            battery_power = battery_power - 1;
        }
        if (battery_power > 0) {
            battery_power = battery_power - battery_power_usage_value;
            if (battery_power < 0) {
                battery_power = 0;
            }
        }
        battery_display_value = battery_power / 10;
        battery_display_value = std::to_string(battery_power / 10);
        battery_caption.setString("Battery: " + battery_display_value + '%');
        ++move_count;
        ++game_time;
        frame_counter_60 = 0;
    }
}

void Main_Game_Window::Draw() {
    game_window.clear();
    // Depends on Scene
    game_window.draw(left_door.getSprite());
    game_window.draw(left_door.getDoorButtonSprite());
    game_window.draw(left_door.getLightButtonSprite());
    game_window.draw(left_door.getDoorButtonCaption());
    game_window.draw(left_door.getLightButtonCaption());
    game_window.draw(bonnie.getSprite());
    game_window.draw(Office_Background_sprite);

    // Always on Screen
    game_window.draw(battery_caption);
    game_window.draw(usage_caption);
    for (int i = 0; i < battery_power_usage_value; i++) {
        usage_bar_sprite.setPosition(sf::Vector2f(485 + (35*i), 21));
        game_window.draw(usage_bar_sprite);
    }
    game_window.draw(clock_text);
    game_window.draw(top_line);
    game_window.draw(bottom_line);
    game_window.display();
}

const bool Main_Game_Window::getdoorClosed() {
    return doorClosed;
}

void Main_Game_Window::setdoorClosed(bool newBool) {
    doorClosed = newBool;
}

const bool Main_Game_Window::getLightsOn() {
    return lightsOn;
}

void Main_Game_Window::setLightsOn(bool newBool) {
    lightsOn = newBool;
}

void Main_Game_Window::Run() {
    while (game_window.isOpen()) {
        if (night_win == true) {
            game_window.close();
        }
        if (night_lose == true) {
            game_window.close();
        }
        //     // Mouse pos collection
        auto mouse_pos = sf::Mouse::getPosition(game_window);
        translated_mouse_pos = game_window.mapPixelToCoords(mouse_pos);

        sf::Event event{};
        while (game_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                game_window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    game_window.close();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (left_door.clickedOn(translated_mouse_pos)) {
                        left_door_open_close_clicked_on = true;
                    }
                    // Quick Light Button Toggle instead of hold
                    if (left_door.getLightButtonSprite().getGlobalBounds().contains(translated_mouse_pos)) {
                        lightsOn = !lightsOn;
                    }
                }
            }
            // Right click hold on door for light mechanic
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                if (left_door.clickedOn(translated_mouse_pos)) {
                    left_door_light_clicked_on = true;
                }
            }
            // Reference for this idea: https://en.sfml-dev.org/forums/index.php?topic=13412.0
            if (event.type == sf::Event::MouseButtonReleased) {
                // If right clicked released for left door light, stop!
                if (left_door.clickedOn(translated_mouse_pos)) {
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        setLightsOn(false);
                        if (doorClosed == false) {
                            left_door.doorLightOff();
                        }
                        // Reset Animatronic Sprites
                        bonnie.resetSprite();
                    }
                }
            }
        }
        Update();
        Draw();
    }
    // // print section to test changes to the game state variables
    std::cout << std::endl;
    std::cout << "Move Counter: " << move_count << std::endl;
    std::cout << "Bonnie Jumpscare Counter: " << bonnie_jumpscare_counter << std::endl;
    std::cout << "Entered Office: " << std::boolalpha << entered_office << std::endl;
    std::cout << "Door Closed: " << std::boolalpha << doorClosed << std::endl;
    std::cout << "Player Alive: " << std::boolalpha << player_alive << std::endl;
    std::cout << "Game Time (in seconds): " << game_time << std::endl;
    std::cout << std::endl;

    if (player_alive) {
        std::cout << "6:00 AM! You lived!" << std::endl;
    }
    else {
        std::cout << "You died..." << std::endl;
    }
}
