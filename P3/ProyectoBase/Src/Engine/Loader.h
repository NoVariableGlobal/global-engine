#pragma once
#include <string>
#include <map>

class Entity;
class ComponentsManager;
class CameraRC;
class Scene;

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
		void readObjects(std::string _fileName, Scene* scene);

		//Create an entity
		void createEntity(Json::Value& _data, int _it, Scene* scene);
};