#include "Main_Game_Window.h"
#include <iostream>
#define FONT_SIZE 35

Main_Game_Window::Main_Game_Window(std::mt19937& rng): night_1(rng), bonnie(20), foxy(20) {
    this->rng = rng;

    night_1.addAnimatronic(bonnie);
    night_1.addFoxy(foxy);
    move_count = 0;
    bonnie_jumpscare_counter = 0;
    foxy_jumpscare_counter = 0;
    number_of_foxy_hits = 0;
    foxy_running = false;
    battery_power = 1000;
    passive_battery_drain_interval = 1000;
    battery_display_value = battery_power / 10;
    battery_power_usage_array = {true, false, false, false};
    battery_power_usage_value = std::count(battery_power_usage_array.begin(),
        battery_power_usage_array.end(), true);
    entered_office = false;
    player_alive = true;
    bonnie_jumpscare = false;
    foxy_jumpscare = false;
    game_time = 0;
    frame_counter_60 = 0;

    night_win = false;
    night_lose = false;

    leftdoorClosed = false;
    leftlightsOn = false;
    left_door_open_close_clicked_on = false;
    left_door_light_clicked_on = false;

    rightdoorClosed = false;
    rightlightsOn = false;
    right_door_open_close_clicked_on = false;
    right_door_light_clicked_on = false;

    open_cam_button_clicked_on = false;
    cam_mode = false;

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
    Office_Background_sprite.setPosition(sf::Vector2f(200,150));
    Office_Background_sprite.setScale(0.94, 0.94);

    map_layout_texture.loadFromFile("src/graphics/fnascii_map.png");
    map_layout_sprite.setTexture(map_layout_texture);
    map_layout_sprite.setPosition(sf::Vector2f(500, 200));

    active_cam = "Cam 1A";

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

    freddy_nose.create(22, 20);
    freddy_nose.clear(sf::Color::Transparent);
    freddy_nose.display();
    freddy_noseSprite.setTexture(freddy_nose.getTexture());
    freddy_noseSprite.setPosition(sf::Vector2f(475, 300));

    freddy_sound_buffer.loadFromFile("src/sound/fnaf_nose_honk.wav");
    jumpscare_sound_buffer.loadFromFile("src/sound/jumpscare.wav");
    open_door_sound_buffer.loadFromFile("src/sound/Open_Door.wav");
    close_door_sound_buffer.loadFromFile("src/sound/Close_Door.wav");
    open_cam_sound_buffer.loadFromFile("src/sound/Open_Cam.wav");
    close_cam_sound_buffer.loadFromFile("src/sound/Close_Cam.wav");
    change_cam_sound_buffer.loadFromFile("src/sound/Change_Cam.wav");
    lights_on_sound_buffer.loadFromFile("src/sound/Light_On.wav");
    lights_off_sound_buffer.loadFromFile("src/sound/Light_Off.wav");
    lights_on_sound_playing = false;
    lights_off_sound_playing = false;
    animatronic_at_door_sound_buffer.loadFromFile("src/sound/Ani_At_door.wav");
    animatronic_sound_playing = false;
    power_zero_buffer.loadFromFile("src/sound/power_zero.wav");
    power_zero_playing = false;
    win_6_am_buffer.loadFromFile("src/sound/Win_6_AM.wav");
    leaving_door_sound_buffer.loadFromFile("src/sound/Leaving_Door.wav");
    foxy_bgm_sound_buffer.loadFromFile("src/sound/foxy_bgm.wav");
    foxy_bgm_sound.setBuffer(foxy_bgm_sound_buffer);
    foxy_bgm_sound.setLoop(true);
    foxy_bgm_sound.setVolume(75.f);
    foxy_bgm_sound_playing = false;
    foxy_running_sound_buffer.loadFromFile("src/sound/Foxy_Running.wav");
    foxy_running_sound.setBuffer(foxy_running_sound_buffer);
    foxy_running_sound_playing = false;

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
        // Check the new cam button
        if (open_cam_button_clicked_on) {
            // Toggle cam mode
            cam_mode = !cam_mode;
            // Play sound corresponding to new state
            if (cam_mode == false) {
                close_cam_sound.setBuffer(close_cam_sound_buffer);
                close_cam_sound.play();
            }
            else {
                open_cam_sound.setBuffer(open_cam_sound_buffer);
                open_cam_sound.play();
            }
            open_cam_button_clicked_on = false;
        }

        // Update Left Door open close toggle
        if (left_door_open_close_clicked_on) {
            setdoorClosed(!getdoorClosed());
            if (leftdoorClosed == true) {
                close_door_sound.setBuffer(close_door_sound_buffer);
                close_door_sound.play();
                std::cout << "You closed the door!" << std::endl;
            }
            else {
                open_door_sound.setBuffer(open_door_sound_buffer);
                open_door_sound.play();
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
        battery_power = 0;
        leftdoorClosed = false;
        leftlightsOn = false;
        cam_mode = false;
        battery_power_usage_array = {false, false, false};
        left_door.doorLightOff();
        left_door.lightButtonOff();
        left_door.openCloseDoor(leftdoorClosed, leftlightsOn);

        lights_on_sound.stop();
        lights_off_sound.stop();

        if (power_zero_playing == false) {
            power_zero_playing = true;
            power_zero_sound.setBuffer(power_zero_buffer);
            power_zero_sound.play();
        }
    }

    // Have Left Door update while lightsOn is true
    if (leftlightsOn) {
        left_door.lightButtonOn();
        if (leftdoorClosed == false) {
            // // If Bonnie is at the door,
            if (night_1.animatronicAtDoorCheck(bonnie, "Left Door")) {
                if (cam_mode == false && animatronic_sound_playing == false) {
                    animatronic_sound_playing = true;
                    animatronic_at_door_sound.setBuffer(animatronic_at_door_sound_buffer);
                    animatronic_at_door_sound.play();
                }
                bonnie.loadAtLeftDoorSprite();
                left_door.doorLightOff();
            }
            else {
                // Reset Animatronic Sprites
                animatronic_sound_playing = false;
                bonnie.resetSprite();
                left_door.doorLightOn();
            }
        }
    }
    else {
        if (leftdoorClosed == false) {
            left_door.doorLightOff();
        }
        left_door.lightButtonOff();
        bonnie.resetSprite();
    }

    // Update array every frame to get faster feedback on usage bar
    if (leftdoorClosed) {
        battery_power_usage_array[1] = true;
    }
    else {
        battery_power_usage_array[1] = false;
    }
    if (leftlightsOn) {
        battery_power_usage_array[2] = true;
    }
    else {
        battery_power_usage_array[2] = false;
    }
    if (cam_mode) {
        battery_power_usage_array[3] = true;
    }
    else {
        battery_power_usage_array[3] = false;
    }
    battery_power_usage_value = std::count(battery_power_usage_array.begin(),
        battery_power_usage_array.end(), true);

    // Music Management
    if (cam_mode == true && active_cam == "Cam 1C") {
        if (foxy_bgm_sound_playing == false) {
            foxy_bgm_sound.play();
            foxy_bgm_sound_playing = true;
        }
    }
    else {
        foxy_bgm_sound.pause();
        foxy_bgm_sound_playing = false;
    }
    if (cam_mode == true && active_cam == "Cam 2A") {
        if (foxy_running) {
            if (foxy_running_sound_playing == false) {
                foxy_running_sound.play();
                foxy_running_sound_playing = true;
            }
        }
    }
    else {
        if (!foxy_running) {
            foxy_running_sound.stop();
        }
        foxy_running_sound_playing = false;
    }

    // Timer engine
    // Manages Bonnie, Foxy, and Battery
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
                bonnie_jumpscare = true;
            }
            bonnie_jumpscare_counter++;
        }
        if (night_1.findAnimatronicCamName(foxy) == "Cam 1C") {
            if (foxy.getStage() == 4) {
                night_1.moveAnimatronic(foxy);
            }
        }
        if (night_1.findAnimatronicCamName(foxy) == "Cam 2A") {
            if (active_cam == "Cam 2A") {
                foxy_running = true;
            }
            if (foxy_running) {
                if (foxy_jumpscare_counter <= 20) {
                    foxy.setFrame(1);
                }
                else {
                    foxy.setFrame(2);
                }
                foxy_jumpscare_counter += 20;
            }
            if (foxy_jumpscare_counter >= 60) {
                if (getdoorClosed() == false) {
                    night_1.enterOffice(foxy);
                    entered_office = true;
                    player_alive = false;
                    night_lose = true;
                    foxy_jumpscare = true;
                }
                else {
                    // Reduce power by number of foxy hits
                    battery_power -= 10 + number_of_foxy_hits * 50;
                    number_of_foxy_hits += 1;
                    leaving_door_sound.setBuffer(leaving_door_sound_buffer);
                    leaving_door_sound.play();
                    animatronic_sound_playing = false;
                    night_1.moveAnimatronic(foxy);
                    foxy_jumpscare_counter = 0;
                    foxy.resetStage();
                    foxy.resetFrame();
                    foxy_running = false;
                }
            }
            foxy_jumpscare_counter++;
        }
        if (move_count == 5) {
            if (night_1.animatronicAtDoorCheck(bonnie, "Left Door")) {
                if (getdoorClosed() == false) {
                    night_1.enterOffice(bonnie);
                    entered_office = true;
                }
                else {
                    leaving_door_sound.setBuffer(leaving_door_sound_buffer);
                    leaving_door_sound.play();
                    animatronic_sound_playing = false;
                }
            }
            if (entered_office == false) {
                // Bonnie
                std::uniform_int_distribution<int> uid(1,20);
                int random_move_value_bonnie = uid(rng);
                if (bonnie.getLevel() >= random_move_value_bonnie) {
                    night_1.moveAnimatronic(bonnie);
                }
                night_1.findAnimatronic(bonnie);

                // Foxy
                int random_move_value_foxy = uid(rng);
                if (foxy.getLevel() >= random_move_value_foxy) {
                    if (night_1.findAnimatronicCamName(foxy) == "Cam 1C") {
                        if (foxy.getStage() < 4) {
                            if (cam_mode == false) {
                                foxy.incrementStage();
                            }
                        }
                    }
                }
                night_1.findAnimatronic(foxy);
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
    if (cam_mode == true) {
        // For drawing cam map and current cam scene
        game_window.draw(map_layout_sprite);
        auto cameras = camera_system.getCameras();
        for (auto &cam : cameras) {
            game_window.draw(cam.getCameraSprite());
        }

        // Vertical Dividing Line
        sf::RectangleShape vertical_line;
        vertical_line.setFillColor(sf::Color::White);
        vertical_line.setOutlineColor(sf::Color::White);
        vertical_line.setSize(sf::Vector2f(0,700));
        vertical_line.setPosition(sf::Vector2f(500, 100));
        vertical_line.setOutlineThickness(1.f);
        game_window.draw(vertical_line);

        // Get current cam scene

        //For foxy stages
        if (active_cam == "Cam 1C") {
            sf::Texture cam1C_texture;
            sf::Sprite cam1C_sprite;
            std::string cam1CDisplay_file_location = "src/graphics/Cam_1C_Stage" + std::to_string(foxy.getStage()) + ".png";
            cam1C_texture.loadFromFile(cam1CDisplay_file_location);
            cam1C_sprite.setTexture(cam1C_texture);
            cam1C_sprite.setPosition(sf::Vector2f(0, 100));
            cam1C_sprite.setScale(sf::Vector2f(1, 1));
            game_window.draw(cam1C_sprite);
        }
        // Every other cam
        else {
            sf::Texture cam_texture;
            sf::Sprite cam_sprite;
            std::string name_for_file = active_cam.substr(0,3) + "_" + active_cam.substr(4);
            std::string camDisplay_file_location = "src/graphics/" + name_for_file + ".png";
            cam_texture.loadFromFile(camDisplay_file_location);
            cam_sprite.setTexture(cam_texture);
            cam_sprite.setPosition(sf::Vector2f(0, 100));
            cam_sprite.setScale(sf::Vector2f(1, 1));
            game_window.draw(cam_sprite);
        }

        // Drawing foxy on Cam 2A
        if (active_cam == "Cam 2A" && foxy_running && night_1.findAnimatronicCamName(foxy) == "Cam 2A") {
            sf::Texture foxy_texture;
            sf::Sprite foxy_sprite;
            foxy_texture.loadFromFile("src/graphics/foxy.png");
            foxy_sprite.setTexture(foxy_texture);
            if (foxy.getFrame() == 1) {
                foxy_sprite.setPosition(sf::Vector2f(200, 200));
                foxy_sprite.setScale(sf::Vector2f(0.5, 0.5));
            }
            else {
                foxy_sprite.setPosition(sf::Vector2f(50, 225));
                foxy_sprite.setScale(sf::Vector2f(1, 1));
            }
            game_window.draw(foxy_sprite);
        }

        // Cam Name bottom left
        sf::Font cam_name_font;
        sf::Text cam_name_text;
        cam_name_font.loadFromFile("src/graphics/font/PixeloidSans.ttf");
        cam_name_text.setFont(cam_name_font);
        cam_name_text.setString(active_cam);
        cam_name_text.setCharacterSize(FONT_SIZE);
        cam_name_text.setFillColor(sf::Color::White);
        cam_name_text.setPosition(sf::Vector2f(10, 750));
        game_window.draw(cam_name_text);

        // This part draws the animatronics onto the scene
        const std::string current_cam_name = active_cam;
        Map::Cam current_camera = night_1.getMap().accessCam(current_cam_name);
        std::vector<std::string> animatronic_names = current_camera.getAnimatronicNames();

        // Print Bonnie on screen if Bonnie is on current cam
        if (std::find(animatronic_names.begin(), animatronic_names.end(), "Bonnie")
            != animatronic_names.end()) {
            sf::Texture bonnie_texture;
            sf::Sprite bonnie_sprite;
            bonnie_texture.loadFromFile("src/graphics/Bonnie_On_Cam.png");
            bonnie_sprite.setTexture(bonnie_texture);
            if (current_cam_name == "Cam 1A") {
                bonnie_sprite.setPosition(sf::Vector2f(0, 200));
                bonnie_sprite.setScale(sf::Vector2f(1, 1));
            }
            else if (current_cam_name == "Cam 1B") {
                bonnie_sprite.setPosition(sf::Vector2f(100, 400));
                bonnie_sprite.setScale(sf::Vector2f(0.5, 0.5));
            }
            else if (current_cam_name == "Cam 2A") {
                bonnie_sprite.setPosition(sf::Vector2f(200, 200));
                bonnie_sprite.setScale(sf::Vector2f(0.5, 0.5));
            }
            else if (current_cam_name == "Cam 2B") {
                bonnie_sprite.setPosition(sf::Vector2f(150, 400));
                bonnie_sprite.setScale(sf::Vector2f(0.7, 0.7));
            }
            else if (current_cam_name == "Cam 3") {
                bonnie_sprite.setPosition(sf::Vector2f(115, 225));
                bonnie_sprite.setScale(sf::Vector2f(1, 1));
            }
            else if (current_cam_name == "Cam 5") {
                bonnie_sprite.setPosition(sf::Vector2f(150, 400));
                bonnie_sprite.setScale(sf::Vector2f(0.7, 0.7));
            }
            if (!(foxy_running && active_cam == "Cam 2A")) {
                game_window.draw(bonnie_sprite);
            }
        }

    }
    if (cam_mode == false) {
        game_window.draw(left_door.getSprite());
        game_window.draw(left_door.getDoorButtonSprite());
        game_window.draw(left_door.getLightButtonSprite());
        game_window.draw(left_door.getDoorButtonCaption());
        game_window.draw(left_door.getLightButtonCaption());
        game_window.draw(right_door.getSprite());
        game_window.draw(right_door.getDoorButtonSprite());
        game_window.draw(right_door.getLightButtonSprite());
        game_window.draw(right_door.getDoorButtonCaption());
        game_window.draw(right_door.getLightButtonCaption());
        game_window.draw(Office_Background_sprite);
        game_window.draw(bonnie.getSprite());
        game_window.draw(freddy_noseSprite);
    }

    if (battery_power <= 0) {
        sf::RenderTexture dark_overlay_texture;
        sf::Sprite dark_overlay_sprite;
        dark_overlay_texture.create(1000, 700);
        dark_overlay_texture.clear(sf::Color::White);
        dark_overlay_texture.display();
        dark_overlay_sprite.setTexture(dark_overlay_texture.getTexture());
        dark_overlay_sprite.setPosition(sf::Vector2f(0, 100));
        dark_overlay_sprite.setColor(sf::Color(0,0,0,128));
        game_window.draw(dark_overlay_sprite);
    }

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
    game_window.draw(open_cam_button.getSprite());
    game_window.display();
}

const bool Main_Game_Window::getdoorClosed() {
    return leftdoorClosed;
}

void Main_Game_Window::setdoorClosed(bool newBool) {
    leftdoorClosed = newBool;
}

const bool Main_Game_Window::getLightsOn() {
    return leftlightsOn;
}

void Main_Game_Window::setLightsOn(bool newBool) {
    leftlightsOn = newBool;
    if (leftlightsOn == true && lights_on_sound_playing == false) {
        lights_on_sound_playing = true;
        lights_off_sound_playing = false;
        lights_on_sound.setBuffer(lights_on_sound_buffer);
        lights_on_sound.play();
    }
    if (leftlightsOn == false && lights_off_sound_playing == false) {
        lights_off_sound_playing = true;
        lights_on_sound_playing = false;
        lights_off_sound.setBuffer(lights_off_sound_buffer);
        lights_off_sound.play();
    }
}

void Main_Game_Window::Run() {
    while (game_window.isOpen()) {
        if (night_win == true) {
            foxy_bgm_sound.stop();
            game_window.clear();
            game_window.display();
            win_6_am_sound.setBuffer(win_6_am_buffer);
            win_6_am_sound.play();
            sf::sleep(sf::seconds(10));
            game_window.close();
        }
        if (night_lose == true) {
            foxy_bgm_sound.stop();
            if (bonnie_jumpscare) {
                sf::Texture bonnie_jumpscare_texture;
                sf::Sprite bonnie_jumpscare_sprite;
                bonnie_jumpscare_sprite.setPosition(125, 75);

                sound_effect.setBuffer(jumpscare_sound_buffer);
                sound_effect.play();

                // Loop frames
                for (int i = 0; i < 5; i++) {
                    game_window.clear();
                    bonnie_jumpscare_texture.loadFromFile("src/graphics/Bonnie_Jumpscare_Frame1.png");
                    bonnie_jumpscare_sprite.setTexture(bonnie_jumpscare_texture);
                    game_window.draw(bonnie_jumpscare_sprite);
                    game_window.display();
                    sf::sleep(sf::seconds(0.25f));
                    game_window.clear();
                    bonnie_jumpscare_texture.loadFromFile("src/graphics/Bonnie_Jumpscare_Frame2.png");
                    bonnie_jumpscare_sprite.setTexture(bonnie_jumpscare_texture);
                    game_window.draw(bonnie_jumpscare_sprite);
                    game_window.display();
                    sf::sleep(sf::seconds(0.25f));
                }
            }
            if (foxy_jumpscare) {
                sf::Texture foxy_jumpscare_texture;
                sf::Sprite foxy_jumpscare_sprite;
                foxy_jumpscare_sprite.setPosition(205, 75);

                sound_effect.setBuffer(jumpscare_sound_buffer);
                sound_effect.play();

                // Loop frames
                for (int i = 0; i < 5; i++) {
                    game_window.clear();
                    foxy_jumpscare_texture.loadFromFile("src/graphics/Foxy_Jumpscare_Frame_1.png");
                    foxy_jumpscare_sprite.setTexture(foxy_jumpscare_texture);
                    game_window.draw(foxy_jumpscare_sprite);
                    game_window.display();
                    sf::sleep(sf::seconds(0.25f));
                    game_window.clear();
                    foxy_jumpscare_texture.loadFromFile("src/graphics/Foxy_Jumpscare_Frame_2.png");
                    foxy_jumpscare_sprite.setTexture(foxy_jumpscare_texture);
                    game_window.draw(foxy_jumpscare_sprite);
                    game_window.display();
                    sf::sleep(sf::seconds(0.25f));
                }
            }
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
                    // In camera
                    if (cam_mode == true) {
                        if (open_cam_button.clickedOn(translated_mouse_pos)) {
                            open_cam_button_clicked_on = true;
                        }
                        // Change camera here
                        std::vector<Camera>& cams = camera_system.getCameras();
                        for (auto& cam : cams) {
                            if (cam.clickedOn(translated_mouse_pos)) {
                                change_cam_sound.setBuffer(change_cam_sound_buffer);
                                change_cam_sound.play();
                                active_cam = cam.getCameraName().getString();
                            }
                        }
                    }
                    // In office
                    if (cam_mode == false) {
                        if (left_door.clickedOn(translated_mouse_pos)) {
                            left_door_open_close_clicked_on = true;
                        }
                        if (open_cam_button.clickedOn(translated_mouse_pos)) {
                            open_cam_button_clicked_on = true;
                        }
                        // Quick Light Button Toggle instead of hold
                        if (left_door.getLightButtonSprite().getGlobalBounds().contains(translated_mouse_pos)) {
                            leftlightsOn = !leftlightsOn;
                            if (leftlightsOn == true) {
                                lights_on_sound.setBuffer(lights_on_sound_buffer);
                                lights_on_sound.play();
                            }
                            else {
                                lights_off_sound.setBuffer(lights_off_sound_buffer);
                                lights_off_sound.play();
                            }
                        }
                        // If Freddy Picture Nose Booped
                        if (freddy_noseSprite.getGlobalBounds().contains(translated_mouse_pos)) {
                            // Play sound
                            sound_effect.setBuffer(freddy_sound_buffer);
                            sound_effect.play();
                        }
                    }
                }
            }
            // Right click hold on door for light mechanic
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                // In camera
                if (cam_mode == true) {
                    // For right-clicking stuff in cam mode
                }
                if (cam_mode == false) {
                    if (left_door.clickedOn(translated_mouse_pos)) {
                        left_door_light_clicked_on = true;
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                // In camera
                if (cam_mode == true) {
                    // future use
                }
                if (cam_mode == false) {
                    // Reference for this idea: https://en.sfml-dev.org/forums/index.php?topic=13412.0
                    // If right-click released for left door light, stop!
                    if (left_door.clickedOn(translated_mouse_pos)) {
                        if (event.mouseButton.button == sf::Mouse::Right) {
                            setLightsOn(false);
                            if (leftdoorClosed == false) {
                                left_door.doorLightOff();
                            }
                            // Reset Animatronic Sprites
                            bonnie.resetSprite();
                        }
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
    std::cout << "Door Closed: " << std::boolalpha << leftdoorClosed << std::endl;
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
