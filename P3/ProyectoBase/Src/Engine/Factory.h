#pragma once

/* Abstract class from which every
   component's factory must inherit */

// Macro for components to register their factory themselves
#define DECLARE_FACTORY(ComponentName)                                         \
    class ComponentName##Factory final : public ComponentFactory {             \
      public:                                                                  \
        ComponentName##Factory();                                              \
                                                                               \
        Component* create(Entity* _father, Json::Value& _data,                 \
                          Scene* _scene) override;                             \
    };                                                                         \
                                                                               \
    class ComponentName##FactoryRegister {                                     \
      public:                                                                  \
        ComponentName##FactoryRegister();                                      \
        void noop();                                                           \
    };                                                                         \
    extern ComponentName##FactoryRegister                                      \
        ComponentName##FactoryRegisterGlobalVar;

#define DEFINE_FACTORY(ComponentName)                                          \
    ComponentName##FactoryRegister::ComponentName##FactoryRegister() {         \
        FactoriesFactory::getInstance()->insert(#ComponentName,                \
                                                new ComponentName##Factory()); \
    }                                                                          \
    void ComponentName##FactoryRegister::noop() {}                             \
    ComponentName##FactoryRegister ComponentName##FactoryRegisterGlobalVar;

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
