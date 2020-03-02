#pragma once

#define REGISTER_FACTORY(name, Component) \
class Component##FactoryRegister { \
    public:\
        Component##FactoryRegister() { \
		FactoriesFactory::instance()->insert(name, new Component##Factory()); } \
}; \
Component##FactoryRegister Component##FactoryRegisterGlobalVar;


namespace Json {
	class Value;
}
class Component;

class ComponentFactory
{
	public:
		ComponentFactory() {};
		virtual Component* create(Json::Value&) = 0;
};

