#include "Adjacency_List.h"

Adjacency_List::Adjacency_List() = default;

const std::map<std::string, std::vector<std::string>> Adjacency_List::getPathMap() const {
    return animatronicPath;
}

void Adjacency_List::addToPath(std::string from, std::string to) {
    animatronicPath[from].push_back(to);
}
