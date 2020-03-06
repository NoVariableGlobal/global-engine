#pragma once
#include <string>
#include <map>

class Entity;
class ComponentsManager;

namespace Json {
	class Value;
}

class Loader
{
	public:
		Loader();
		~Loader();

		//Read the scenes from secnes.json file
		void readScenes(std::map<std::string, std::string>& _scenesQueue);

		//Read the entities of the scene from the scene file
		void readEntities(std::string _fileName, std::map<std::string, Entity*>& _entities, ComponentsManager* componentManager);

		//Create an entity
		void createEntity(Json::Value& _data, int _it, std::map<std::string, Entity*>& _entities, ComponentsManager* componentManager);
};