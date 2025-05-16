#include <fstream>
#include "tom_engine/game/Main_Game_Window/Main_Game_Window.h"
#include "tom_engine/game/Home_Screen_Window/Home_Screen_Window.h"
#include "tom_engine/game/Custom_Night_Settings_Window/Custom_Night_Settings_Window.h"

// Note: snake_case for variable names, camelCase for functions

// random number generator:
// Reference: https://stackoverflow.com/questions/29549873/stdmt19937-doesnt-return-random-number
static std::random_device rd;
static std::mt19937 rng{rd()};

int main() {
    bool quit = false;

    while (!quit) {
        // Fstream to FNASCII Player Data
        // First line is what night player will continue from (1-5)
        // Second line is how many stars they earned (3 stars for 100%)
        std::fstream fnascii_fstream("src/savefiles/fnascii_player_data.txt");
        std::string night_to_continue;
        getline(fnascii_fstream, night_to_continue);

        std::string stars_earned;
        getline(fnascii_fstream, stars_earned);

        Home_Screen_Window home_screen(std::stoi(night_to_continue), std::stoi(stars_earned));
        std::string selected_night = home_screen.Run();

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
            Main_Game_Window night_1(rng, 1, 3, 0, 0, 0);
            bool player_alive = night_1.Run();

            // Night 2
            if (player_alive) {
                fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                                    std::fstream::out | std::fstream::trunc);
                night_to_continue = "2";
                fnascii_fstream << night_to_continue << std::endl << stars_earned;
                fnascii_fstream.close();

                Main_Game_Window night_2(rng, 2, 3, 1, 1, 0);
                player_alive = night_2.Run();
            }

            // Night 3
            if (player_alive) {
                fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                                    std::fstream::out | std::fstream::trunc);
                night_to_continue = "3";
                fnascii_fstream << night_to_continue << std::endl << stars_earned;
                fnascii_fstream.close();

                Main_Game_Window night_3(rng, 3, 0, 2, 5, 1);
                player_alive = night_3.Run();
            }

            // Night 4
            if (player_alive) {
                fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                    std::fstream::out | std::fstream::trunc);
                night_to_continue = "4";
                fnascii_fstream << night_to_continue << std::endl << stars_earned;
                fnascii_fstream.close();

                Main_Game_Window night_4(rng, 4, 2, 6, 4, 2);
                player_alive = night_4.Run();
            }

            // Night 5
            if (player_alive) {
                fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                    std::fstream::out | std::fstream::trunc);
                night_to_continue = "5";
                fnascii_fstream << night_to_continue << std::endl << stars_earned;
                fnascii_fstream.close();

                Main_Game_Window night_5(rng, 5, 5, 5, 7, 3);
                player_alive = night_5.Run();
            }

            if (player_alive) {
                fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                    std::fstream::out | std::fstream::trunc);
                if (std::stoi(stars_earned) < 1) {
                    stars_earned = "1";
                }
                fnascii_fstream << night_to_continue << std::endl << stars_earned;
                fnascii_fstream.close();
            }
        }

        if (selected_night == "Continue Game") {
            // Continue the game until the player dies
            // Update save each night

            bool player_alive = true;
            int continue_num = std::stoi(night_to_continue);

            // Night 1
            if (continue_num == 1) {
                Main_Game_Window night_1(rng, 1, 3, 0, 0, 0);
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
                Main_Game_Window night_2(rng, 2, 3, 1, 1, 0);
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

                Main_Game_Window night_3(rng, 3, 0, 2, 5, 1);
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
                Main_Game_Window night_4(rng, 4, 2, 6, 4, 2);
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
                Main_Game_Window night_5(rng, 5, 5, 5, 7, 3);
                player_alive = night_5.Run();
            }

            if (player_alive && continue_num == 5) {
                fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                    std::fstream::out | std::fstream::trunc);
                if (std::stoi(stars_earned) < 1) {
                    stars_earned = "1";
                }
                fnascii_fstream << night_to_continue << std::endl << stars_earned;
                fnascii_fstream.close();
            }
        }
        if (selected_night == "6th Night") {
            Main_Game_Window night_6(rng, 6, 10, 6, 12, 4);
            bool player_alive = night_6.Run();

            if (player_alive) {
                fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                    std::fstream::out | std::fstream::trunc);
                if (std::stoi(stars_earned) < 2) {
                    stars_earned = "2";
                }
                fnascii_fstream << night_to_continue << std::endl << stars_earned;
                fnascii_fstream.close();
            }
        }
        if (selected_night == "Custom Night") {
            Custom_Night_Settings_Window custom_night_settings_window;
            custom_night_settings_window.Run();
            int freddy_level = custom_night_settings_window.getFreddyLevel();
            int foxy_level = custom_night_settings_window.getFoxyLevel();
            int bonnie_level = custom_night_settings_window.getBonnieLevel();
            int chica_level = custom_night_settings_window.getChicaLevel();

            Main_Game_Window night_7(rng, 7, bonnie_level, foxy_level, chica_level, freddy_level);
            bool player_alive = night_7.Run();

            if (player_alive) {
                // Only write if 4/20 mode
                if (freddy_level == 20 && foxy_level == 20 && chica_level == 20 && bonnie_level == 20) {
                    fnascii_fstream.open("src/savefiles/fnascii_player_data.txt", std::fstream::in |
                        std::fstream::out | std::fstream::trunc);
                    if (std::stoi(stars_earned) < 3) {
                        stars_earned = "3";
                    }
                    fnascii_fstream << night_to_continue << std::endl << stars_earned;
                    fnascii_fstream.close();
                }
            }
        }
    }

    return 0;
}
