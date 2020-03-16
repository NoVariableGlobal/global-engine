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
	entity->setMaterialName(material);
}

// FACTORY INFRASTRUCTURE
class TridimensionalObjectRCFactory : public ComponentFactory {
public:
	TridimensionalObjectRCFactory() {};

	virtual Component* create(Entity* _father, Json::Value& _data, ComponentsManager* _componentManager)
	{
		Ogre::SceneManager* mSM = OgreSDLContext::getInstance()->getSceneManager();
		TridimensionalObjectRC* tridimensionalObject = new TridimensionalObjectRC();

		tridimensionalObject->setFather(_father);

		if (!_data["mesh"].isString()) throw std::exception("TridimensionalObjectRC: mesh is not a string");
		tridimensionalObject->setOgreEntity(mSM->createEntity(_data["mesh"].asString()));

		if (!_data["node"].isString()) throw std::exception("TridimensionalObjectRC: node is not a string");
		tridimensionalObject->setSceneNode(mSM->getRootSceneNode()->createChildSceneNode(_data["node"].asString()));

		if (!_data["material"].isString()) throw std::exception("TridimensionalObjectRC: material is not a string");
		tridimensionalObject->setMaterial(_data["material"].asString());

		tridimensionalObject->getSceneNode()->attachObject(tridimensionalObject->getOgreEntity());

		TransformComponent* transform = dynamic_cast<TransformComponent*>(_father->getComponent("TransformComponent"));
		tridimensionalObject->getSceneNode()->setPosition(transform->getPosition());
		tridimensionalObject->getSceneNode()->setScale(transform->getScale());

		_componentManager->addRC(tridimensionalObject);
		return tridimensionalObject;
	}
};

REGISTER_FACTORY("TridimensionalObjectRC", TridimensionalObjectRC);
