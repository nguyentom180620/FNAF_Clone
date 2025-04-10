#include <SFML/Graphics.hpp>
#include <random>
#include "tom_engine/game/Main_Game_Window/Main_Game_Window.h"
// Note: snake_case for variable names, camelCase for functions

// random number generator:
// Reference: https://stackoverflow.com/questions/29549873/stdmt19937-doesnt-return-random-number
static std::random_device rd;
static std::mt19937 rng{rd()};

/* TODO: Draw the Office, making sure to use transparent + sf::RenderNONE
 * After that, cam system and scene manager
*/

int main() {
    Main_Game_Window main_game_window(rng);
    main_game_window.Run();

    return 0;
}
