#pragma once
#include <map>
#include <string>

class Entity;
class ComponentsManager;
class CameraRC;
class Scene;

namespace Json {
    class Value;
}

class Loader {
  public:
    Loader();
    ~Loader();

    // Read the scenes from secnes.json file
    void readScenes(std::map<std::string, std::string>& _scenesQueue);

    // Read the prefabs from the prefab file
    void readPrefabs(Scene* scene);
    // Create a prefab
    void createPrefab(Json::Value& _data, Scene* scene);

    // Read the entities of the scene from the scene file
    void readObjects(std::string _fileName, Scene* scene);
    // Create an entity
    void createEntity(Json::Value& _data, Scene* scene);
    // Set the components to an entity
    void setComponents(Json::Value& _data, Entity* _entity, Scene* scene);
};