#pragma once
#include<map>
#include<string>

class Component;

class ComponentFactory
{
	public:
		ComponentFactory() {};
		virtual Component* create() = 0;
};

std::map<std::string, ComponentFactory*> factory;