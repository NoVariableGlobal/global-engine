#pragma once

/* Abstract class from which every
   component's factory must inherit */

// Macro for components to register their factory themselves
#define REGISTER_FACTORY(name, Component)                                      \
    class Component##FactoryRegister {                                         \
      public:                                                                  \
        Component##FactoryRegister() {                                         \
            FactoriesFactory::getInstance()->insert(name,                      \
                                                    new Component##Factory()); \
        }                                                                      \
        static void noop() {};                                                  \
    };                                                                         \
    Component##FactoryRegister Component##FactoryRegisterGlobalVar;

namespace Json {
    class Value;
}

class Component;
class Entity;
class ComponentsManager;
class Scene;

class ComponentFactory {
  public:
    ComponentFactory() = default;
    virtual ~ComponentFactory() = default;
    virtual Component* create(Entity* father, Json::Value&, Scene* scene) = 0;
};
