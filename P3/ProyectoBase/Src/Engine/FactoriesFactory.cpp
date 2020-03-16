#include "FactoriesFactory.h"
#include "Factory.h"

FactoriesFactory* FactoriesFactory::_instance = nullptr;

FactoriesFactory::FactoriesFactory() {}

void FactoriesFactory::clear()
{
	for (auto it : factory)
	{
		delete it.second;
	}
	delete _instance;
}

FactoriesFactory* FactoriesFactory::getInstance()
{
	return _instance;
}

void FactoriesFactory::init()
{
	_instance = new FactoriesFactory();
}

void FactoriesFactory::insert(std::string name, ComponentFactory* fac)
{
	factory.insert({ name, fac });
}

ComponentFactory* FactoriesFactory::find(std::string name)
{
	return factory.find(name)->second;
}
