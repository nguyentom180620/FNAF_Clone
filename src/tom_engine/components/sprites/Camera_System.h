#pragma once
#include <vector>
#include "Camera.h"

class Camera_System {
    std::vector<Camera> cameras;
public:
    Camera_System();
    std::vector<Camera>& getCameras();
};

