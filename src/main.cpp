#include <SFML/Graphics.hpp>
#include <iostream>
#include "tom_engine/game_night/Game_Night.h"

int main() {
    Game_Night night_1;
    night_1.playNight();

    return 0;
}

// int main() {
//     auto window = sf::RenderWindow{ { 1000u, 900u }, "FNAF Clone" };
//     window.setFramerateLimit(60);
//
//     while (window.isOpen()) {
//         sf::Event event {};
//         while(window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }
//             if (event.type == sf::Event::KeyPressed) {
//                 if (event.key.code == sf::Keyboard::Escape) {
//                     window.close();
//                 }
//             }
//         }
//
//         window.clear();
//         window.display();
//     }
//
//     return 0;
// }
