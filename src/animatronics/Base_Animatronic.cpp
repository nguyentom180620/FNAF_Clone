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
