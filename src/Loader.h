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
    // Read the scenes from scenes.json file
    void readScenes(std::map<std::string, std::string>& _scenesQueue);

    // Read the prefabs from the prefab file
    void readPrefabs(Scene* scene);
    // Create a prefab
    void createPrefab(Json::Value& data, Scene* scene);

    // Read the entities of the scene from the scene file
    void readObjects(const std::string& fileName, Scene* scene);

    // Read the sounds of the game from the sounds file
    void readSounds();

    void createSoundInfo(Json::Value& data);

    // Create an entity
    void createEntity(Json::Value& data, Scene* scene);
    // Set the components to an entity
    void setComponents(Json::Value& data, Entity* entity, Scene* scene);
};