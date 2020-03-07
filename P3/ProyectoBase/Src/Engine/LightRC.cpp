#include <json.h>

#include "LightRC.h"
#include "Entity.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "ComponentsManager.h"
#include "TransformComponent.h"
#include "OgreEntity.h"
#include "OgreSDLContext.h"
#include "OgreSceneManager.h"

// COMPONENT CODE
LightRC::LightRC() {}

LightRC::~LightRC() {}

void LightRC::render() {}

// FACTORY INFRASTRUCTURE
class LightRCFactory : public ComponentFactory {
public:
	LightRCFactory() {};

	virtual Component* create(Entity* father, Json::Value& _data, ComponentsManager* componentManager)
	{
		Ogre::SceneManager* mSM = OgreSDLContext::getInstance()->getSceneManager();
		LightRC* light = new LightRC();
		
		light->setFather(father);
		light->setOgreEntity(mSM->createEntity(_data["mesh"].asString()));
		light->setSceneNode(mSM->getRootSceneNode()->createChildSceneNode(_data["node"].asString()));
		light->getSceneNode()->attachObject(light->getOgreEntity());

		TransformComponent* transform = dynamic_cast<TransformComponent*>(father->getComponent("TransformComponent"));
		light->getSceneNode()->setPosition(transform->getPosition());
		light->getSceneNode()->setScale(transform->getScale());

		// Pendiente de unificar un metodo con las fisicas y otros que necesiten rotacion
		//Ogre::Vector3 ori = transform->getOrientation();
		//tridimensionalObject->getSceneNode()->setOrientation(0, ori.x, ori.y, ori.z);

		componentManager->addRC(light);
		return light;
	};
};

REGISTER_FACTORY("LightRC", LightRC);