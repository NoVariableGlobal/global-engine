#include "TestChangeSceneIC.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "ComponentsManager.h"
#include "Scene.h"

#include "OgreRoot.h"

#include <json.h>

#include <iostream>

TestChangeSceneIC::TestChangeSceneIC() {}

TestChangeSceneIC::~TestChangeSceneIC() {}

void TestChangeSceneIC::handleInput(const SDL_Event& _event)
{
	if (_event.type == SDL_KEYDOWN)
	{
		if (_event.key.keysym.sym == SDLK_SPACE)
			scene->changeScene("Game");
	}
}


// FACTORY INFRASTRUCTURE
class TestChangeSceneICFactory : public ComponentFactory {
public:
	TestChangeSceneICFactory() {};
	virtual Component* create(Entity* _father, Json::Value& _data, Scene* _scene)
	{
		TestChangeSceneIC* change = new TestChangeSceneIC();
		_scene->getComponentsManager()->addIC(change);

		change->setFather(_father);
		change->setScene(_scene);

		return change;
	};
};

REGISTER_FACTORY("TestChangeSceneIC", TestChangeSceneIC);
