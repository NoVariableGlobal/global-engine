#pragma once

class Component;

class ComponentFactory
{
	public:
		ComponentFactory(/*Json::Value&*/) {};
		virtual Component* create() = 0;
};

