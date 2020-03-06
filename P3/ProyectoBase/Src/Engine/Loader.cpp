#include "Loader.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Ogre.h"
#include "OgreVector3.h"
#include "ComponentsManager.h"
#include "CameraObject.h"

#include <json.h>
#include <fstream>
#include <string>

Loader::Loader() {}

Loader::~Loader() {}

void Loader::readScenes(std::map<std::string, std::string>& _scenesQueue)
{
	std::fstream file;
	file.open("files/scenes.json");

	if (file.is_open())
	{
		Json::Value data;
		file >> data;
		data = data["scenes"];

		int numScenes = data.size();
		for (int i = 0; i < numScenes; i++)
			_scenesQueue.emplace(data[i]["name"].asString(), data[i]["file"].asString());
	}
	else
	{
		// LANZAR EXCEPCION
	}

}

void Loader::readObjects(std::string _fileName, CameraObject* _cam, std::map<std::string, Entity*>& _entities, ComponentsManager* componentManager)
{
	std::fstream file;
	file.open("files/" + _fileName);

	if (file.is_open())
	{
		Json::Value data;
		file >> data;

		Json::Value entities = data["entities"];
		int numEntities = entities.size();
		for (int i = 0; i < numEntities; i++)
			createEntity(entities[i], i, _entities, componentManager);

		Json::Value camera = data["camera"];
		createCamera(camera, _cam);
	}
	else
	{
		// LANZAR EXCEPCION
	}
}

void Loader::createEntity(Json::Value& _data, int _it, std::map<std::string, Entity*>& _entities, ComponentsManager* componentManager)
{
	Entity* entity = new Entity();

	// ID of the Entity
	entity->setId(_data["id"].asString());

	// List of COMPONENTS to add to the Entity
	Json::Value components = _data["components"];

	int numComponents = components.size();
	for (int i = 0; i < numComponents; i++)
		entity->addComponent(components[i]["type"].asString(), FactoriesFactory::getInstance()->find(components[i]["type"].asString())->create(entity, components[i]["attributes"], componentManager));

	_entities.emplace(entity->getId(), entity);
}

void Loader::createCamera(Json::Value& _data, CameraObject* _cam)
{
	_cam->setCameraOffset(Ogre::Vector3(_data["offset"][0].asInt(), _data["offset"][1].asInt(), _data["offset"][2].asInt()));
	_cam->setPosition(Ogre::Vector3(_data["position"][0].asInt(), _data["position"][1].asInt(), _data["position"][2].asInt()));

	if (_data["lookAt"].asString() != "none")
		_cam->lookAt(Ogre::Vector3(_data["lookAt"][0].asInt(), _data["lookAt"][1].asInt(), _data["lookAt"][2].asInt()));
}
