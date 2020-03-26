#include "FactoriesFactory.h"
#include "Factory.h"

#include <iostream>

FactoriesFactory* FactoriesFactory::_instance = nullptr;

FactoriesFactory::FactoriesFactory() {}

void FactoriesFactory::clear() {
    for (auto it : factory) {
        delete it.second;
    }
    delete _instance;
}

FactoriesFactory* FactoriesFactory::getInstance() {
    if (_instance == nullptr)
        _instance = new FactoriesFactory();
    return _instance;
}

void FactoriesFactory::insert(std::string name, ComponentFactory* fac) {
    factory.insert({name, fac});
}

ComponentFactory* FactoriesFactory::find(std::string name) {
    auto it = factory.find(name);
    if (it == factory.end()) {
        std::cout << "ERROR: Factory '" + name + "' could not be found\n";
        throw std::exception("Factory could not be found");
    }
    return it->second;
}
