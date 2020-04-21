#include "Loader.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"
#include <Ogre.h>

#include <iostream>
#include <json.h>
#include <string>

#include "SoundContext.h"

void Loader::readScenes(std::map<std::string, std::string>& _scenesQueue) {
    std::fstream file;
    file.open("files/scenes.json");

    if (!file.is_open())
        throw std::exception("Loader: files/scenes.json not found");

    Json::Value data;
    file >> data;

    if (!data["scenes"].isArray())
        throw std::exception(
            "Loader: files/scenes.json: scenes is not an array");

    data = data["scenes"];

    const int numScenes = data.size();
    for (int i = 0; i < numScenes; i++) {
        if (!data[i]["name"].isString() || !data[i]["file"].isString())
            throw std::exception(
                "Loader: files/scenes.json: name or file are not a string");
        _scenesQueue.emplace(data[i]["name"].asString(),
                             data[i]["file"].asString());
    }
}

void Loader::readPrefabs(Scene* scene) {
    std::fstream file;
    file.open("files/prefabs.json");

    if (!file.is_open())
        throw std::exception("Loader: files/prefabs.json not found");

    Json::Value data;
    file >> data;

    if (!data["prefabs"].isArray())
        throw std::exception(
            "Loader: files/prefabs.json: prefabs is not an array");
    Json::Value prefabs = data["prefabs"];

    const int numPrefabs = prefabs.size();
    for (int i = 0; i < numPrefabs; i++)
        createPrefab(prefabs[i], scene);
}

void Loader::createPrefab(Json::Value& data, Scene* scene) {
    if (!data["id"].isString())
        throw std::exception("Loader: files/prefabs.json: id is not a string");
    const std::string id = data["id"].asString();

    if (!data["components"].isArray())
        throw std::exception(
            "Loader: files/prefabs.json: components is not an array");
    const Json::Value components = data["components"];

    scene->addPrefab(id, components);
}

void Loader::readObjects(const std::string& fileName, Scene* scene) {
    std::fstream file;
    file.open("files/" + fileName);

    if (!file.is_open())
        throw std::exception("Loader: scene file not found");

    Json::Value data;
    file >> data;

    if (!data["entities"].isArray())
        throw std::exception("Loader: scene file: entities is not an array");

    Json::Value entities = data["entities"];

    const int numEntities = entities.size();
    for (int i = 0; i < numEntities; i++)
        createEntity(entities[i], scene);
}

void Loader::readSounds() {
    std::fstream file;
    file.open("files/sounds.json");
    if (!file.is_open())
        throw std::exception("Loader: sounds file not found");

    Json::Value data;
    file >> data;

    if (!data["sounds"].isArray())
        throw std::exception("Loader: scene file: sounds is not an array");

    Json::Value sounds = data["sounds"];

    const int numSounds = sounds.size();
    for (int i = 0; i < numSounds; ++i)
        createSoundInfo(sounds[i]);
}

void Loader::createSoundInfo(Json::Value& data) {
    if (!data["id"].isString())
        throw std::exception(
            "Loader: files/sounds.json: id is not an string. ");
    if (!data["filename"].isString())
        throw std::exception(
            "Loader: files/sounds.json: filename is not an string. ");
    if (!data["loop"].isBool())
        throw std::exception("Loader: files/sounds.json: loop is not a bool. ");
    if (!data["volume"].isDouble())
        throw std::exception(
            "Loader: files/sounds.json: loop is not a double. ");
    auto* info = new SoundInfo();
    info->id = data["id"].asString();
    info->filename = data["filename"].asString();
    info->loop = data["loop"].asBool();
    info->volume = data["volume"].asFloat();

    SoundContext::getInstance()->addSoundToLoad(info);
}

void Loader::createEntity(Json::Value& data, Scene* scene) {
    auto* entity = new Entity();

    if (!data["id"].isString())
        throw std::exception("Loader: id is not string");
    entity->setId(data["id"].asString());

    if (data["tag"].isString())
        entity->setTag(data["tag"].asString());

    if (data["persistent"].isBool())
        entity->setPersistent(data["persistent"].asBool());

    scene->addEntity(entity);

    if (!data["components"].isArray())
        throw std::exception("Loader: components is not an array");
    Json::Value components = data["components"];

    setComponents(components, entity, scene);
}

void Loader::setComponents(Json::Value& data, Entity* entity, Scene* scene) {
    const int numComponents = data.size();
    for (int i = 0; i < numComponents; i++) {
        if (!data[i]["type"].isString() || !data[i]["attributes"].isObject())
            throw std::exception(
                "Loader: type is not a string or attributes is not an Object");
        entity->addComponent(
            data[i]["type"].asString(),
            FactoriesFactory::getInstance()
                ->find(data[i]["type"].asString())
                ->create(entity, data[i]["attributes"], scene));
    }
}
