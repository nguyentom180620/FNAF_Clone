#pragma once
#include "../Base_Animatronic/Base_Animatronic.h"

class Foxy : public Base_Animatronic {
    int stage;
    int running_frame;
public:
    Foxy(int l, std::string s = "Foxy");
    int getStage();
    void incrementStage();
    void resetStage();
    int getFrame();
    void setFrame(int frame);
    void resetFrame();
};
