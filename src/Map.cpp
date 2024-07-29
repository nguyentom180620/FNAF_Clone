#include "Map.h"

bool Map::isCam(std::string cam) {
    if (cams.find(cam) != cams.end()) {
        return true;
    }
    return false;
}


Map::Map() {
    cams["Cam 1A"] = Cam("Cam 1A");
    cams["Cam 1B"] = Cam("Cam 1B");
    cams["Cam 1C"] = Cam("Cam 1C");
    cams["Cam 2A"] = Cam("Cam 2A");
    cams["Cam 2B"] = Cam("Cam 2B");
    cams["Cam 3"] = Cam("Cam 3");
    cams["Cam 4A"] = Cam("Cam 4A");
    cams["Cam 4B"] = Cam("Cam 4B");
    cams["Cam 5"] = Cam("Cam 5");
    cams["Cam 6"] = Cam("Cam 6");
    cams["Cam 7"] = Cam("Cam 7");
}

void Map::printCamContent(std::string cam) {
    // For now, have it print out cam name when user looks for it
    // Accept inputs like: Cam 1A, cam 1A, cam 1a, 1A, and 1a

    // Below lambda allows for easy, repeated function for two cases
    auto lastLetterUpperCasing = [](std::string& s, int i) -> void {
        if (s.size() == i) {
            char temp = std::toupper(s[i-1]);
            s[i-1] = temp;
        }
    };

    std::string cam_name;
    if (cam.size() < 3) {
        lastLetterUpperCasing(cam, 2);
        cam_name = "Cam ";
        cam_name += cam;
    }
    else {
        if (!cam.empty()) {
            char temp = std::toupper(cam[0]);
            cam[0] = temp;
        }
        lastLetterUpperCasing(cam, 6);
        cam_name = cam;
    }
    if (isCam(cam_name)) {
        std::cout << "Cam name: " << cams[cam_name].getName() << std::endl;
    }
    else {
        std::cout << "Cam not found, try again" << std::endl;
    }
}
