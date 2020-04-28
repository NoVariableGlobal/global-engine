#include "FactoriesFactory.h"
#include "Factory.h"
#include "Util.h"

FactoriesFactory* FactoriesFactory::instance_ = nullptr;

FactoriesFactory::FactoriesFactory() = default;

void FactoriesFactory::clear() {
    for (const auto& it : factory_) {
        delete it.second;
    }
    delete instance_;
}

FactoriesFactory* FactoriesFactory::getInstance() {
    if (instance_ == nullptr)
        instance_ = new FactoriesFactory();
    return instance_;
}

void FactoriesFactory::insert(const std::string& name, ComponentFactory* fac) {
    factory_.insert({name, fac});
}

ComponentFactory* FactoriesFactory::find(const std::string& name) const {
    return assert_find(factory_, name);
}
