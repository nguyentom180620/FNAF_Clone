#include <SFML/Graphics.hpp>
#include <random>
#include "tom_engine/game_night/Game_Night.h"
#include "graphics/Left_Door.h"

// random number generator:
// Reference: https://stackoverflow.com/questions/29549873/stdmt19937-doesnt-return-random-number
static std::random_device rd;
static std::mt19937 rng{rd()};

// font is same as Notepad, consolas 11 font
constexpr unsigned int FONT_SIZE = 17;

// int main() {
//     Game_Night night_1(rng);
//     night_1.playNight();
//
//     return 0;
// }

int main() {
    auto window = sf::RenderWindow{ { 1000u, 900u }, "FNAF Clone" };
    window.setFramerateLimit(60);

    // Left Door ASCII Text Import
    sf::Font font;
    font.loadFromFile("src/graphics/font/consolas.ttf");

    sf::Text left_door_text(left_door_open_empty_text, font);
    left_door_text.setCharacterSize(FONT_SIZE);
    left_door_text.setStyle(sf::Text::Regular);
    left_door_text.setFillColor(sf::Color::White);

    // Try drawing left door using render texture
    sf::RenderTexture left_door_render_texture;
    if (!left_door_render_texture.create(100, 325)) {
        return -1;
    }

    // Make inital left door sprite
    sf::Sprite left_door_sprite;
    left_door_sprite.setTexture(left_door_render_texture.getTexture());

    // Mouse click checking for door
    // Logic from here: https://en.sfml-dev.org/forums/index.php?topic=21666.0
    auto mouse_pos = sf::Mouse::getPosition(window);
    sf::Vector2f translated_pos;

    while (window.isOpen()) {
        // Mouse pos collection
        mouse_pos = sf::Mouse::getPosition(window);
        translated_pos = window.mapPixelToCoords(mouse_pos);

        sf::Event event {};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (left_door_sprite.getGlobalBounds().contains(translated_pos)) {
                        std::cout << "You are clicking the door!" << std::endl;
                    }
                }
            }
        }
        left_door_render_texture.clear(sf::Color::Black);
        left_door_render_texture.draw(left_door_text);
        left_door_render_texture.display();

        window.clear();
        left_door_sprite.setTexture(left_door_render_texture.getTexture());
        left_door_sprite.setPosition(sf::Vector2f(97.f, 236.f));
        window.draw(left_door_sprite);
        window.display();
    }

    // Game_Night night_1(rng);
    //
    // // GAME STATE SECTION
    // // This loads the night before the gameplay window starts
    // // Idea is to load everything, and then while window is open the game changes as we pass time through frames
    // Bonnie bonnie(1);
    // night_1.addAnimatronic(bonnie);
    //
    // int move_count = 0;
    // int bonnie_jumpscare_counter = 0;
    // bool enteredOffice = false;
    // bool doorClosed = false;
    // bool playerAlive = true;
    // int gameTime = 0;
    // int frameCounter60 = 0;
    //
    // while (window.isOpen()) {
    //     sf::Event event {};
    //     while(window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed) {
    //             window.close();
    //         }
    //         if (event.type == sf::Event::KeyPressed) {
    //             if (event.key.code == sf::Keyboard::Escape) {
    //                 window.close();
    //             }
    //             if (event.key.code == sf::Keyboard::Space) {
    //                 // Open and Close Door
    //                 if (!doorClosed) {
    //                     std::cout << "You closed the door!" << std::endl;
    //                     doorClosed = true;
    //                 }
    //                 else {
    //                     std::cout << "You opened the door!" << std::endl;
    //                     doorClosed = false;
    //                 }
    //             }
    //         }
    //     }
    //
    //     window.clear();
    //     window.display();
    //
    //     // Game Timer
    //     // Idea: Since frame rate is locked at 60, have another variable hold that count so that
    //     // once it becomes 60, the game count increments and the 60 is reset to 0
    //     // Essentially, this is our while loop for the game
    //     ++frameCounter60;
    //     if (frameCounter60 >= 60) {
    //         if (gameTime >= GAME_LENGTH) {
    //             break;
    //         }
    //         switch (gameTime) {
    //             case 0:
    //                 std::cout << "12 AM" << std::endl;
    //             break;
    //             case 90:
    //                 std::cout << "1 AM" << std::endl;
    //             break;
    //             case 179:
    //                 std::cout << "2 AM" << std::endl;
    //             break;
    //             case 268:
    //                 std::cout << "3 AM" << std::endl;
    //             break;
    //             case 357:
    //                 std::cout << "4 AM" << std::endl;
    //             break;
    //             case 446:
    //                 std::cout << "5 AM" << std::endl;
    //             break;
    //             case GAME_LENGTH:
    //                 std::cout << "6 AM" << std::endl;
    //             break;
    //             default: break;
    //         }
    //         if (night_1.animatronicInOffice()) {
    //             if (bonnie_jumpscare_counter >= 3) {
    //                 std::cout << "Bonnie Jumpscare!" << std::endl;
    //                 playerAlive = false;
    //                 break;
    //             }
    //             bonnie_jumpscare_counter++;
    //         }
    //         if (move_count == 5) {
    //             if (night_1.animatronicAtDoorCheck(bonnie, "Left Door")) {
    //                 if (!doorClosed) {
    //                     night_1.enterOffice(bonnie);
    //                     enteredOffice = true;
    //                 }
    //                 else {
    //                     std::cout << "Bonnie hit the door, he's gone now but broke the door!" << std::endl;
    //                     doorClosed = false;
    //                 }
    //             }
    //             if (!enteredOffice) {
    //                 night_1.moveAnimatronic(bonnie);
    //                 night_1.findAnimatronic(bonnie);
    //             }
    //             move_count = 0;
    //         }
    //         ++move_count;
    //         ++gameTime;
    //         frameCounter60 = 0;
    //     }
    // }
    //
    // // print section to test changes to the game state variables
    // std::cout << std::endl;
    // std::cout << "Move Counter: " << move_count << std::endl;
    // std::cout << "Bonnie Jumpscare Counter: " << bonnie_jumpscare_counter << std::endl;
    // std::cout << "Entered Office: " << std::boolalpha << enteredOffice << std::endl;
    // std::cout << "Door Closed: " << std::boolalpha << doorClosed << std::endl;
    // std::cout << "Player Alive: " << std::boolalpha << playerAlive << std::endl;
    // std::cout << "Game Time (in seconds): " << gameTime << std::endl;
    // std::cout << std::endl;
    //
    // if (playerAlive) {
    //     std::cout << "6:00 AM! You lived!" << std::endl;
    // }
    // else {
    //     std::cout << "You died..." << std::endl;
    // }

    return 0;
}
