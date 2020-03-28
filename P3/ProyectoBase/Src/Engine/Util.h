#pragma once

#include <iostream>
#include <map>
#include <string>

template <typename T>
T assert_find(std::map<std::string, T> map, std::string name) {
    auto it = map.find(name);
    if (it == map.end()) {
        std::string type = typeid(T).name();
        std::cout << "ERROR: Resource '" + name + "' of type '" + type +
                         "' could not be found\n";
        throw std::exception("Resource could not be found");
    }
    return it->second;
}
