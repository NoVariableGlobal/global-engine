#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

template <typename T>
T try_find(std::map<std::string, T> map, std::string name) {
    auto it = map.find(name);
    if (it == map.end())
        return nullptr;
    else
        return it->second;
}

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

template <typename T>
void assert_deleteComponent(std::vector<T>& deleteVector,
                            std::vector<T>& vector) {
    if (deleteVector.size() > 0) {
        bool erased = false;
        auto itDelete = deleteVector.begin();
        while (itDelete != deleteVector.end()) {
            auto it = vector.begin();
            while (it != vector.end() && !erased) {
                if ((*it) == (*itDelete)) {
                    delete *it;
                    erased = true;
                } else
                    ++it;
            }
            erased = false;
            if (it != vector.end())
                vector.erase(it);
            else {
                std::string type = typeid(T).name();
                std::cout << "ERROR: Component of type '" + type +
                                 "' could not be deleted\n";
                throw std::exception("Component could not be deleted, it "
                                     "probably was already deleted before\n");
            }

            ++itDelete;
        }
        deleteVector.clear();
    }
}