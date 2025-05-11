#include "Foxy.h"

Foxy::Foxy(int l, std::string s) : Base_Animatronic(s, l) {
    // Set path map
    path.addToPath("Cam 1C", "Cam 2A");
    path.addToPath("Cam 2A", "Cam 1C");
    stage = 1;
    running_frame = 1;
}

int Foxy::getStage() {
    return stage;
}

void Foxy::incrementStage() {
    stage += 1;
}

void Foxy::resetStage() {
    stage = 1;
}

int Foxy::getFrame() {
    return running_frame;
}

void Foxy::setFrame(int frame) {
    running_frame = frame;
}

void Foxy::resetFrame() {
    running_frame = 1;
}