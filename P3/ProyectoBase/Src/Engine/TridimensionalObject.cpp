#include <json.h>

#include "TridimensionalObject.h"
#include "Entity.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "ComponentsManager.h"
#include "TransformComponent.h"
#include "OgreVector3.h"
#include "OgreEntity.h"
#include "OgreSDLContext.h"
#include "OgreSceneManager.h"

// COMPONENT CODE
TridimensionalObject::TridimensionalObject() {}

TridimensionalObject::~TridimensionalObject() {
	_entity = nullptr;
	_sceneNode = nullptr;
}

void TridimensionalObject::render() {}

void TridimensionalObject::setMaterial(std::string material) {
	_entity->setMaterialName(material);
}

// GETTERS AND SETTERS
Ogre::Entity* TridimensionalObject::getOgreEntity() { return _entity; }
void TridimensionalObject::setOgreEntity(Ogre::Entity* e) {	_entity = e; }

Ogre::SceneNode* TridimensionalObject::getSceneNode() {	return _sceneNode; }
void TridimensionalObject::setSceneNode(Ogre::SceneNode* sn) { _sceneNode = sn; }

// FACTORY INFRASTRUCTURE
class TridimensionalObjectFactory : public ComponentFactory {
public:
	TridimensionalObjectFactory() {};

	virtual Component* create(Entity* father, Json::Value& _data, ComponentsManager* componentManager)
	{
		Ogre::SceneManager* mSM = OgreSDLContext::getInstance()->getSceneManager();
		TridimensionalObject* tridimensionalObject = new TridimensionalObject();
		
		tridimensionalObject->setFather(father);
		tridimensionalObject->setOgreEntity(mSM->createEntity(_data["mesh"].asString()));
		tridimensionalObject->setSceneNode(mSM->getRootSceneNode()->createChildSceneNode(_data["node"].asString()));
		tridimensionalObject->setMaterial(_data["material"].asString());
		tridimensionalObject->getSceneNode()->attachObject(tridimensionalObject->getOgreEntity());

		TransformComponent* transform = dynamic_cast<TransformComponent*>(father->getComponent("TransformComponent"));
		Ogre::Vector3 ori = transform->getOrientation();
		tridimensionalObject->getSceneNode()->setPosition(transform->getPosition());
		//tridimensionalObject->getSceneNode()->setOrientation(0, ori.x, ori.y, ori.z);
		tridimensionalObject->getSceneNode()->setScale(transform->getScale());
		
		componentManager->addRC(tridimensionalObject);
		return tridimensionalObject;
	};
};

REGISTER_FACTORY("TridimensionalObject", TridimensionalObject);