#pragma once
#include <string>
#include <vector>
#include <map>

class Adjacency_List {
    std::map<std::string, std::vector<std::string>> animatronicPath;
public:
    Adjacency_List();
    const std::map<std::string, std::vector<std::string>> getPathMap() const;
    void addToPath(std::string from, std::string to);
};
