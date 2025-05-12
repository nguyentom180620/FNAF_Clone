#pragma once
#include "../Base_Animatronic/Base_Animatronic.h"

class Freddy : public Base_Animatronic {
    int moving_song_number;
public:
    Freddy(int l, std::string s = "Freddy");
    int getMovingSongNumber();
    void setMovingSongNumber(int song_number);
};
