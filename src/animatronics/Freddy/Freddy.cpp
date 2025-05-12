#include "Freddy.h"

Freddy::Freddy(int l, std::string s) : Base_Animatronic(s, l) {
    // Set path map
    path.addToPath("Cam 1A", "Cam 1B");
    path.addToPath("Cam 1B", "Cam 7");
    path.addToPath("Cam 7", "Cam 6");
    path.addToPath("Cam 6", "Cam 4A");
    path.addToPath("Cam 4A", "Cam 4B");
    path.addToPath("Cam 4B", "Cam 4A");
    moving_song_number = 1;
}

int Freddy::getMovingSongNumber() {
    return moving_song_number;
}

void Freddy::setMovingSongNumber(int song_number) {
    moving_song_number = song_number;
}