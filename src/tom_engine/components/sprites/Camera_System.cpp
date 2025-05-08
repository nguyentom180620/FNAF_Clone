#include "Camera_System.h"

Camera_System::Camera_System() {
    Camera Cam1A("Cam 1A", sf::Vector2f(650, 205));
    cameras.push_back(Cam1A);
}

std::vector<Camera>& Camera_System::getCameras() {
    return cameras;
}