#pragma once
#include<map>
#include<string>

class Component;
class ComponentFactory;

class FactoriesFactory
{
	private:
		static FactoriesFactory* _instance;
		static std::map<std::string, ComponentFactory*> factory;
		FactoriesFactory();

	public:
		static FactoriesFactory* getInstance();
		void insert(std::string name, ComponentFactory* fac);
		ComponentFactory* find(std::string name);
		void erase();
		
};

