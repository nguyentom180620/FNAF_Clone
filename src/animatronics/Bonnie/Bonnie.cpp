#include "Bonnie.h"

Bonnie::Bonnie(int l, std::string s) : Base_Animatronic(s, l) {
    path.addToPath("Cam 1A", "Cam 1B");
    path.addToPath("Cam 1A", "Cam 5");
    path.addToPath("Cam 1B", "Cam 2A");
    path.addToPath("Cam 1B", "Cam 5");
    path.addToPath("Cam 2A", "Cam 2B");
    path.addToPath("Cam 2A", "Cam 3");
    path.addToPath("Cam 2B", "Cam 3");
    path.addToPath("Cam 2B", "Left Door");
    path.addToPath("Cam 3", "Cam 2A");
    path.addToPath("Cam 3", "Left Door");
    path.addToPath("Cam 5", "Cam 1B");
    path.addToPath("Cam 5", "Cam 2A");
    path.addToPath("Left Door", "Cam 1B");
}
