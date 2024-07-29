#include <SFML/Graphics.hpp>
#include<iostream>
#include "map/Map.h"

int main() {
    Map map;
    std::string input;
    while (true) {
        getline(std::cin, input);
        if (input == "end") {
            break;
        }

        map.printCamContent(input);
    }

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
