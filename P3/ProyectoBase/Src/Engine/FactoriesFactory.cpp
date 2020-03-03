#include "FactoriesFactory.h"
#include "Factory.h"

std::map<std::string, ComponentFactory*> FactoriesFactory::factory;
FactoriesFactory* FactoriesFactory::_instance = nullptr;

FactoriesFactory* FactoriesFactory::instance()
{
	if (_instance == nullptr) _instance = new FactoriesFactory();
	return _instance;
}

void FactoriesFactory::insert(std::string name, ComponentFactory* fac)
{
	factory.insert({ name, fac });
}

ComponentFactory* FactoriesFactory::find(std::string name)
{
	return factory.find(name)->second;
}