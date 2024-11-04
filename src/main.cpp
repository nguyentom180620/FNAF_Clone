#include <SFML/Graphics.hpp>
#include <random>
#include "tom_engine/game_night_backend/Game_Night_Backend.h"
#include "tom_engine/game/Main_Game_Window/Main_Game_Window.h"
// Note: snake_case for variable names, camelCase for functions

// random number generator:
// Reference: https://stackoverflow.com/questions/29549873/stdmt19937-doesnt-return-random-number
static std::random_device rd;
static std::mt19937 rng{rd()};

// font is same as Notepad, consolas font
constexpr unsigned int FONT_SIZE = 17;

/* TODO: Implement Door and Light Buttons and make them interactable, then connect Bonnie to game and test interaction!
 * Basically, get the graphic version up to the current playtest function so we can practice seeing Bonnie in ASCII!
 * Maybe even make a jumpscare animation?
 * ASCII starting to come in!
*/

// int main() {
//     Game_Night night_1(rng);
//     night_1.playNight();
//
//     return 0;
// }

int main() {
    Main_Game_Window main_game_window{};
    main_game_window.Run();

    // Game_Night night_1(rng);

    // GAME STATE SECTION
    // This loads the night before the gameplay window starts
    // Idea is to load everything, and then while window is open the game changes as we pass time through frames
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
