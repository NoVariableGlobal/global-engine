#include <json.h>

#include "TridimensionalObjectRC.h"
#include "Entity.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "ComponentsManager.h"
#include "TransformComponent.h"
#include "OgreEntity.h"
#include "OgreSDLContext.h"
#include "OgreSceneManager.h"

// COMPONENT CODE
TridimensionalObjectRC::TridimensionalObjectRC() {}

TridimensionalObjectRC::~TridimensionalObjectRC() {}

void TridimensionalObjectRC::render() {}

void TridimensionalObjectRC::setMaterial(std::string material) {
	_entity->setMaterialName(material);
}

// FACTORY INFRASTRUCTURE
class TridimensionalObjectFactory : public ComponentFactory {
public:
	TridimensionalObjectFactory() {};

	virtual Component* create(Entity* father, Json::Value& _data, ComponentsManager* componentManager)
	{
		Ogre::SceneManager* mSM = OgreSDLContext::getInstance()->getSceneManager();
		TridimensionalObjectRC* tridimensionalObject = new TridimensionalObjectRC();
		
		tridimensionalObject->setFather(father);
		tridimensionalObject->setOgreEntity(mSM->createEntity(_data["mesh"].asString()));
		tridimensionalObject->setSceneNode(mSM->getRootSceneNode()->createChildSceneNode(_data["node"].asString()));
		tridimensionalObject->setMaterial(_data["material"].asString());
		tridimensionalObject->getSceneNode()->attachObject(tridimensionalObject->getOgreEntity());

		TransformComponent* transform = dynamic_cast<TransformComponent*>(father->getComponent("TransformComponent"));
		tridimensionalObject->getSceneNode()->setPosition(transform->getPosition());
		tridimensionalObject->getSceneNode()->setScale(transform->getScale());

		// Pendiente de unificar un metodo con las fisicas y otros que necesiten rotacion
		//Ogre::Vector3 ori = transform->getOrientation();
		//tridimensionalObject->getSceneNode()->setOrientation(0, ori.x, ori.y, ori.z);

		componentManager->addRC(tridimensionalObject);
		return tridimensionalObject;
	};
};

REGISTER_FACTORY("TridimensionalObject", TridimensionalObject);