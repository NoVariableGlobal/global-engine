#include "Loader.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Ogre.h"
#include "OgreVector3.h"
#include "ComponentsManager.h"
#include "TransformComponent.h"

#include <json.h>
#include <iostream>
#include <string>

#include <stdexcept>

Loader::Loader() {}

Loader::~Loader() {}

void Loader::readScenes(std::map<std::string, std::string>& _scenesQueue)
{
	std::fstream file;
	file.open("files/scenes.json");

	if (!file.is_open()) throw std::exception("Loader: files/scenes.json not found");

	Json::Value data;
	file >> data;

	if (!data["scenes"].isArray()) throw std::exception("Loader: files/scenes.json: scenes is not an array");

	data = data["scenes"];

	int numScenes = data.size();
	for (int i = 0; i < numScenes; i++)
	{
		if (!data[i]["name"].isString() || !data[i]["file"].isString()) throw std::exception("Loader: files/scenes.json: name or file are not a string");
			_scenesQueue.emplace(data[i]["name"].asString(), data[i]["file"].asString());
	}
}

void Loader::readObjects(std::string _fileName, std::map<std::string, Entity*>& _entities, ComponentsManager* componentManager)
{
	std::fstream file;
	file.open("files/" + _fileName);

	if (!file.is_open()) throw std::exception("Loader: scene file not found");

	Json::Value data;
	file >> data;

	if (!data["entities"].isArray()) throw std::exception("Loader: scene file: entities is not an array");

	Json::Value entities = data["entities"];

	int numEntities = entities.size();
	for (int i = 0; i < numEntities; i++)
		createEntity(entities[i], i, _entities, componentManager);
}

void Loader::createEntity(Json::Value& _data, int _it, std::map<std::string, Entity*>& _entities, ComponentsManager* componentManager)
{
	Entity* entity = new Entity();

	if (!_data["id"].isString()) throw std::exception("Loader: id is not string");

	entity->setId(_data["id"].asString());

	if (!_data["components"].isArray()) throw std::exception("Loader: components is not an array");
	Json::Value components = _data["components"];

	int numComponents = components.size();
	for (int i = 0; i < numComponents; i++)
	{
		// PREGUNTAR A MIRIAM SOBRE ESTO
		if (!components[i]["type"].isString() && !components[i]["attributes"].isArray()) throw std::exception("Loader: type is not a string or attributes is not array");

		entity->addComponent(components[i]["type"].asString(), FactoriesFactory::getInstance()->find(components[i]["type"].asString())->create(entity, components[i]["attributes"], componentManager));
	}

	_entities.emplace(entity->getId(), entity);
}