#include <json.h>

#include "SpotLightRC.h"
#include "Entity.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "ComponentsManager.h"
#include "TransformComponent.h"
#include "OgreEntity.h"
#include "OgreSDLContext.h"
#include "OgreSceneManager.h"
#include "Scene.h"

// COMPONENT CODE
SpotLightRC::SpotLightRC() {}

SpotLightRC::~SpotLightRC() {}

void SpotLightRC::setLight(std::string _entityID)
{
	_msM = OgreSDLContext::getInstance()->getSceneManager();


	light = _msM->createLight(_entityID + "Light");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
}

Ogre::Light* SpotLightRC::getLight() { return light; }

void SpotLightRC::setColour(Ogre::Vector3 _colour)
{
	light->setDiffuseColour(_colour.x, _colour.y, _colour.z);
}

void SpotLightRC::setDirection(Ogre::Vector3 _dir)
{
	sceneNode->setDirection(Ogre::Vector3(_dir.x, _dir.y, _dir.z));
}

void SpotLightRC::render() {}

// FACTORY INFRASTRUCTURE
class SpotLightRCFactory : public ComponentFactory {
public:
	SpotLightRCFactory() {};

	virtual Component* create(Entity* _father, Json::Value& _data, Scene* scene)
	{
		Ogre::SceneManager* mSM = OgreSDLContext::getInstance()->getSceneManager();
		SpotLightRC* light = new SpotLightRC();

		light->setFather(_father);
		light->setScene(scene);

		light->setLight(_father->getId());

		if (!_data["node"].isString()) { /*EXCEPCION*/ }
		light->setSceneNode(mSM->getRootSceneNode()->createChildSceneNode(_data["node"].asString()));
		light->getSceneNode()->attachObject(light->getLight());

		if (!_data["colour"].isArray()) { /*EXCEPCION*/ }
		light->setColour(Ogre::Vector3(_data["colour"][0].asFloat(), _data["colour"][1].asFloat(), _data["colour"][2].asFloat()));

		if (!_data["direction"].isArray()) { /*EXCEPCION*/ }
		light->setDirection(Ogre::Vector3(_data["direction"][0].asFloat(), _data["direction"][1].asFloat(), _data["direction"][2].asFloat()));

		scene->getComponentsManager()->addRC(light);

		return light;
	};
};

REGISTER_FACTORY("SpotLightRC", SpotLightRC);