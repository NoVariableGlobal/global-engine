#pragma once
#include<map>
#include<string>

class Component;
class ComponentFactory;

class FactoriesFactory
{
	private:
		static FactoriesFactory* _instance;

		// Map of components and their factories for the engine to create
	    std::map<std::string, ComponentFactory*> factory;

		FactoriesFactory();

	public:
		// Creates the instance if needed and returns it
		static FactoriesFactory* getInstance();

		// Returns the factory of a given component
		ComponentFactory* find(std::string name);

		// Insert a component and its factory into the map
		void insert(std::string name, ComponentFactory* fac);

		// Empties the factories map and destroys the instance
		void clear();	
};

