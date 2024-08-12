#include <SFML/Graphics.hpp>
#include <random>
#include "tom_engine/game_night/Game_Night.h"

// random number generator:
// Reference: https://stackoverflow.com/questions/29549873/stdmt19937-doesnt-return-random-number
// TODO: FIGURE OUT HOW TO USE WINDOW TIME TO INFLUENCE GAMENIGHT, FOR NOW BEGINNNING OF BONNIE IS DONE!
static std::random_device rd;
static std::mt19937 rng{rd()};

// int main() {
//     Game_Night night_1(rng);
//     night_1.playNight();
//
//     return 0;
// }

int main() {
    auto window = sf::RenderWindow{ { 1000u, 900u }, "FNAF Clone" };
    window.setFramerateLimit(60);

    Game_Night night_1(rng);

    while (window.isOpen()) {
        sf::Event event {};
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}
