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

void Loader::readPrefabs(Scene* scene)
{
	std::fstream file;
	file.open("files/prefabs.json");

	if (!file.is_open()) { /*EXCEPCION*/ }

	Json::Value data;
	file >> data;

	if (!data["prefabs"].isArray()) { /*EXCEPCION*/ }
	Json::Value prefabs = data["prefabs"];

	int numPrefabs = prefabs.size();
	for (int i = 0; i < numPrefabs; i++)
		createPrefab(prefabs[i], scene);
}

void Loader::createPrefab(Json::Value& _data, Scene* _scene)
{
	if (!_data["id"].isString()) { /*EXCEPCION*/ }
	std::string id = _data["id"].asString();

	if (!_data["components"].isArray()) { /*EXCEPCION*/ }
	Json::Value components = _data["components"];

	_scene->addPrefab(id, components);
}

void Loader::readObjects(std::string _fileName, Scene* _scene)
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
		createEntity(entities[i], _scene);
}

void Loader::createEntity(Json::Value& _data, Scene* _scene)
{
	Entity* entity = new Entity();

	if (!_data["id"].isString()) { /*EXCEPCION*/ }
	entity->setId(_data["id"].asString());

	if (!_data["components"].isArray()) { /*EXCEPCION*/ }
	Json::Value components = _data["components"];

	setComponents(components, entity, _scene);

	_scene->addEntity(entity);
}

void Loader::setComponents(Json::Value& _data, Entity* _entity, Scene* _scene)
{
	int numComponents = _data.size();
	for (int i = 0; i < numComponents; i++)
	{
		if (!_data[i]["type"].isString() || !_data[i]["attributes"].isArray()) { /*EXCEPCION*/ }
		_entity->addComponent(_data[i]["type"].asString(), FactoriesFactory::getInstance()->find(_data[i]["type"].asString())->create(_entity, _data[i]["attributes"], _scene));
	}
}
