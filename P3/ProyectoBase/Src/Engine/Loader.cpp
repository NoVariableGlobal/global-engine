#include "Loader.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Ogre.h"
#include "OgreVector3.h"
#include "ComponentsManager.h"
#include "TransformComponent.h"
#include "Scene.h"

#include <json.h>
#include <fstream>
#include <string>

Loader::Loader() {}

Loader::~Loader() {}

void Loader::readScenes(std::map<std::string, std::string>& _scenesQueue)
{
	std::fstream file;
	file.open("files/scenes.json");

	if (!file.is_open()) { /*EXCEPCION*/ }

	Json::Value data;
	file >> data;

	if (!data["scenes"].isArray()) { /*EXCEPCION*/ }
	data = data["scenes"];

	int numScenes = data.size();
	for (int i = 0; i < numScenes; i++)
	{
		if (!data[i]["name"].isString() || !data[i]["file"].isString()) { /*EXCEPCION*/ }
		_scenesQueue.emplace(data[i]["name"].asString(), data[i]["file"].asString());
	}

}

void Loader::readObjects(std::string _fileName, Scene* scene)
{
	std::fstream file;
	file.open("files/" + _fileName);

	if (!file.is_open()) { /*EXCEPCION*/ }

	Json::Value data;
	file >> data;

	if (!data["entities"].isArray()) { /*EXCEPCION*/ }
	Json::Value entities = data["entities"];

	int numEntities = entities.size();
	for (int i = 0; i < numEntities; i++)
		createEntity(entities[i], i, scene);
}

void Loader::createEntity(Json::Value& _data, int _it, Scene* scene)
{
	Entity* entity = new Entity();

	if (!_data["id"].isString()) { /*EXCEPCION*/ }
	entity->setId(_data["id"].asString());

	if (!_data["components"].isArray()) { /*EXCEPCION*/ }
	Json::Value components = _data["components"];

	int numComponents = components.size();
	for (int i = 0; i < numComponents; i++)
	{
		if (!components[i]["type"].isString() || !components[i]["attributes"].isArray()) { /*EXCEPCION*/ }
		entity->addComponent(components[i]["type"].asString(), FactoriesFactory::getInstance()->find(components[i]["type"].asString())->create(entity, components[i]["attributes"], scene));
	}

	scene->addEntity(entity);
}