#include "Map.h"

constexpr unsigned int NUM_OF_ANIMATRONICS = 4;

Map::Cam::Cam() {
    for (int i = 0; i < NUM_OF_ANIMATRONICS; i++) {
        animatronics.push_back(nullptr);
    }
}

Map::Cam::Cam(std::string n) {
    name = n;

    for (int i = 0; i < NUM_OF_ANIMATRONICS; i++) {
        animatronics.push_back(nullptr);
    }
}

std::string Map::Cam::getName() {
    return name;
}

const std::string Map::Cam::getName() const {
    return name;
}

void Map::Cam::addAnimatronic(Base_Animatronic& base) {
    for (int i = 0; i < animatronics.size(); i++) {
        if (animatronics[i] == nullptr) {
            animatronics[i] = &base;
            break;
        }
    }
}

void Map::Cam::removeAnimatronic(Base_Animatronic &base) {
    for (int i = 0; i < animatronics.size(); i++) {
        if (!animatronics[i]) {
            continue;
        }
        if (*animatronics[i] == base) {
            animatronics[i] = nullptr;
            break;
        }
    }
}

std::vector<std::string> Map::Cam::getAnimatronicNames() {
    std::vector<std::string> animatronicNames {};
    for (const auto i : animatronics) {
        if (i != nullptr) {
            animatronicNames.push_back(i->getName());
        }
    }
    return animatronicNames;
}

const std::vector<std::string> Map::Cam::getAnimatronicNames() const {
    std::vector<std::string> animatronicNames {};
    for (const auto i : animatronics) {
        if (i != nullptr) {
            animatronicNames.push_back(i->getName());
        }
    }
    return animatronicNames;
}

bool Map::Cam::operator==(Cam const &rhsCam) const {
    if (name==rhsCam.name && animatronics == rhsCam.animatronics) {
        return true;
    }
    return false;
}

bool Map::isCam(const std::string& cam) {
    if (cams.find(cam) != cams.end()) {
        return true;
    }
    return false;
}

const std::unordered_map<std::string, Map::Cam> Map::getCams() const {
    return cams;
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
    // Left door will be a cam that is accessible differently from the rest in graphic version of game
    cams["Left Door"] = Cam("Left Door");
}

Map::Cam &Map::accessCam(const std::string &cam_name) {
    return cams[cam_name];
}

const Map::Cam &Map::accessCam(std::string& cam_name) const {
    return cams.at(cam_name);
}

Map::Cam Map::find(Base_Animatronic const &base) {
    std::string base_name = base.getName();
    auto iter = cams.begin();
    for (; iter != cams.end(); ++iter) {
        const std::vector<std::string> animatronicNames = iter->second.getAnimatronicNames();
        for (const auto& i : animatronicNames) {
            if (i == base_name) {
                return iter->second;
            }
        }
    }
    return Cam("null");
}

const Map::Cam Map::find(Base_Animatronic const &base) const {
    std::string base_name = base.getName();
    auto iter = cams.begin();
    for (; iter != cams.end(); ++iter) {
        const std::vector<std::string> animatronicNames = iter->second.getAnimatronicNames();
        for (const auto& i : animatronicNames) {
            if (i == base_name) {
                return iter->second;
            }
        }
    }
    return Cam("null");
}


void Map::addAnimatronic(Base_Animatronic &base) {
    cams["Cam 1A"].addAnimatronic(base);
}

void Map::moveAnimatronic(Base_Animatronic &base, Cam& oldCam, Cam& newCam) {
    oldCam.removeAnimatronic(base);
    newCam.addAnimatronic(base);
}

void letterUpperCasing (std::string& s, int i) {
    if (i >= 0 && i < s.size()) {
        s[i] = std::toupper(s[i]);
    }
};

void Map::printCamContent(std::string& cam) {
    // For now, have it print out cam name when user looks for it
    // Accept inputs like: Cam 1A, cam 1A, cam 1a, 1A, and 1a

    std::string cam_name = "";
    if (cam.size() >= 1) {
        if (cam.size() < 3) {
            letterUpperCasing(cam, 1);
            cam_name = "Cam ";
            cam_name += cam;
        }
        else {
            // First one changes for first element
            letterUpperCasing(cam, 0);
            letterUpperCasing(cam, 5);
            cam_name = cam;
        }
    }

    // Here is the first test, where cam just prints its cam name
    // if (isCam(cam_name)) {
    //     std::cout << "Cam name: " << cams[cam_name].getName() << std::endl;
    // }
    // else {
    //     std::cout << "Cam not found, try again" << std::endl;
    // }

    // Here is a test now to get the names of the animatronic at the cam!
    if (isCam(cam_name)) {
        std::vector<std::string> animatronicNames = cams[cam_name].getAnimatronicNames();
        std::cout << cams[cam_name].getName() << ": ";
        if (animatronicNames.empty()) {
            std::cout << "Nobody" << std::endl;
        }
        else {
            for (int i = 0; i < animatronicNames.size() - 1; i++) {
                std::cout << animatronicNames[i] << ", ";
            }
            std::cout << animatronicNames.back() << std::endl;
        }
    }
    else {
        std::cout << "Cam not found, try again" << std::endl;
    }
}

bool Map::animatronicAtDoor(Base_Animatronic &base, std::string door) {
    if (find(base) == cams[door]) {
        return true;
    }
    return false;
}
