#include <SFML/Graphics.hpp>
#include <random>
#include "tom_engine/game/Main_Game_Window/Main_Game_Window.h"
// Note: snake_case for variable names, camelCase for functions

// random number generator:
// Reference: https://stackoverflow.com/questions/29549873/stdmt19937-doesnt-return-random-number
static std::random_device rd;
static std::mt19937 rng{rd()};

/* TODO: Graphics connected to Backend! Now, we should add the light mechanic and draw Bonnie at door if he's there
 * Still do the door and light buttons, clicking on door will just be QOL shortcut
 * After that, drawing the rest of the office would be a nice next step
*/

int main() {
    Main_Game_Window main_game_window(rng);
    main_game_window.Run();

    return 0;
}
