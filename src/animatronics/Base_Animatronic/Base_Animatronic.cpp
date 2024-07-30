#include "Base_Animatronic.h"

Base_Animatronic::Base_Animatronic() {
    name = "Base";
    level = 1;
}

Base_Animatronic::Base_Animatronic(std::string n, int l) {
    name = n;
    level = l;
}

std::string Base_Animatronic::getName() {
    return name;
}

const std::string Base_Animatronic::getName() const {
    return name;
}

int Base_Animatronic::getLevel() {
    return level;
}

const int Base_Animatronic::getLevel() const {
    return level;
}

bool Base_Animatronic::operator==(Base_Animatronic const& base) const {
    if (name == base.getName() && level == base.getLevel()) {
        return true;
    }
    return false;
}
