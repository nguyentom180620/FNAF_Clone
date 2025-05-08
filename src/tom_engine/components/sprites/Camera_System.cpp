#include "Camera_System.h"

Camera_System::Camera_System() {
    Camera Cam1A("Cam 1A", sf::Vector2f(650, 205));
    Camera Cam1B("Cam 1B", sf::Vector2f(675, 300));
    Camera Cam1C("Cam 1C", sf::Vector2f(582, 357));
    Camera Cam2A("Cam 2A", sf::Vector2f(625, 515));
    Camera Cam2B("Cam 2B", sf::Vector2f(600, 625));
    Camera Cam3("Cam 3", sf::Vector2f(533, 433));
    Camera Cam4A("Cam 4A", sf::Vector2f(730,515));
    Camera Cam4B("Cam 4B", sf::Vector2f(758, 625));
    Camera Cam5("Cam 5", sf::Vector2f(505 , 205));
    Camera Cam6("Cam 6", sf::Vector2f(890, 450));
    Camera Cam7("Cam 7", sf::Vector2f(900, 205));
    cameras.push_back(Cam1A);
    cameras.push_back(Cam1B);
    cameras.push_back(Cam1C);
    cameras.push_back(Cam2A);
    cameras.push_back(Cam2B);
    cameras.push_back(Cam3);
    cameras.push_back(Cam4A);
    cameras.push_back(Cam4B);
    cameras.push_back(Cam5);
    cameras.push_back(Cam6);
    cameras.push_back(Cam7);
}

std::vector<Camera>& Camera_System::getCameras() {
    return cameras;
}