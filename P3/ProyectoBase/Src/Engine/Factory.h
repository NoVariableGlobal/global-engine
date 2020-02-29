#pragma once

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

