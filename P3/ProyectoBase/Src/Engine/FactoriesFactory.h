#pragma once
#include<map>
#include<string>

class Component;
class ComponentFactory;

class FactoriesFactory
{
	private:
		static FactoriesFactory* _instance;
	    std::map<std::string, ComponentFactory*> factory;
		FactoriesFactory();

	public:
		static FactoriesFactory* getInstance();
		static void init();

		ComponentFactory* find(std::string name);
		void insert(std::string name, ComponentFactory* fac);
		void clear();	
};

