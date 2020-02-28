#include "Loader.h"
#include "Entity.h"

#include <json.h>
#include <fstream>
#include <string>

Loader::Loader() {}

Loader::~Loader() {}

void Loader::readScenes(std::map<std::string, std::string>& _scenesQueue)
{
	std::fstream file;
	file.open("Files/scenes.json");

	if (file.is_open())
	{
		Json::Value data;
		file >> data;
		data = data["scenes"];

		int numScenes = data.size();
		for (int i = 0; i < numScenes; i++)
			_scenesQueue.emplace(data[i]["name"].asString(), data[i]["file"].asString());
	}

}

void Loader::readEntities(std::string _fileName, std::map<std::string*, Entity*>& _entities)
{
	std::fstream file;
	file.open("Files/" + _fileName);

	if (file.is_open())
	{
		Json::Value data;
		file >> data;
		data = data["entities"];

		int numEntities = data.size();
		for (int i = 0; i < numEntities; i++)
			createEntity(data, i, _entities);
	}
}

void Loader::createEntity(Json::Value& _data, int _it, std::map<std::string*, Entity*>& _entities)
{
	Entity* entity = new Entity();

	// Set ID to the Entity
	entity->setId(_data[_it]["id"].asString());

	// Set COMPONENTS to the Entity
	Json::Value components = _data[_it]["components"];

	int numComponents = components.size();
	for (int j = 0; j < numComponents; j++)
	{
	}
}
