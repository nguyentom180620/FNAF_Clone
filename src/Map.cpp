#include "Map.h"

Map::Map() {
    cams["Cam_1A"] = Cam("Cam_1A");
    cams["Cam_1B"] = Cam("Cam_1B");
    cams["Cam_1C"] = Cam("Cam_1C");
    cams["Cam_2A"] = Cam("Cam_2A");
    cams["Cam_2B"] = Cam("Cam_2B");
    cams["Cam_3"] = Cam("Cam_3");
    cams["Cam_4A"] = Cam("Cam_4A");
    cams["Cam_4B"] = Cam("Cam_4B");
    cams["Cam_5"] = Cam("Cam_5");
    cams["Cam_6"] = Cam("Cam_6");
    cams["Cam_7"] = Cam("Cam_7");
}

bool Map::isCam(std::string cam) {
    if (cams.find(cam) != cams.end()) {
        return true;
    }
    return false;
}
