#include "Loader.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Ogre.h"
#include "Scene.h"

#include <iostream>
#include <json.h>
#include <string>

#include "SoundContext.h"

Loader::Loader() {}

Loader::~Loader() {}

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

    int numScenes = data.size();
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

    int numPrefabs = prefabs.size();
    for (int i = 0; i < numPrefabs; i++)
        createPrefab(prefabs[i], scene);
}

void Loader::createPrefab(Json::Value& _data, Scene* _scene) {
    if (!_data["id"].isString())
        throw std::exception("Loader: files/prefabs.json: id is not a string");
    std::string id = _data["id"].asString();

    if (!_data["components"].isArray())
        throw std::exception(
            "Loader: files/prefabs.json: components is not an array");
    Json::Value components = _data["components"];

    _scene->addPrefab(id, components);
}

void Loader::readObjects(std::string _fileName, Scene* _scene) {
    std::fstream file;
    file.open("files/" + _fileName);

    if (!file.is_open())
        throw std::exception("Loader: scene file not found");

    Json::Value data;
    file >> data;

    if (!data["entities"].isArray())
        throw std::exception("Loader: scene file: entities is not an array");

    Json::Value entities = data["entities"];

    int numEntities = entities.size();
    for (int i = 0; i < numEntities; i++)
        createEntity(entities[i], _scene);
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

    int numSounds = sounds.size();
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
    SoundInfo* info = new SoundInfo;
    info->id = data["id"].asString();
    info->filename = data["filename"].asString();
    info->loop = data["loop"].asBool();
    info->volume = data["volume"].asFloat();

    SoundContext::getInstance()->addSoundToLoad(info);
}

void Loader::createEntity(Json::Value& _data, Scene* _scene) {
    Entity* entity = new Entity();

    if (!_data["id"].isString())
        throw std::exception("Loader: id is not string");
    entity->setId(_data["id"].asString());

    if (_data["tag"].isString())
        entity->setTag(_data["tag"].asString());

    if (_data["persistent"].isBool())
        entity->setPersistent(_data["persistent"].asBool());

    _scene->addEntity(entity);

    if (!_data["components"].isArray())
        throw std::exception("Loader: components is not an array");
    Json::Value components = _data["components"];

    setComponents(components, entity, _scene);
}

void Loader::setComponents(Json::Value& _data, Entity* _entity, Scene* _scene) {
    int numComponents = _data.size();
    for (int i = 0; i < numComponents; i++) {
        if (!_data[i]["type"].isString() || !_data[i]["attributes"].isObject())
            throw std::exception(
                "Loader: type is not a string or attributes is not an Object");
        _entity->addComponent(
            _data[i]["type"].asString(),
            FactoriesFactory::getInstance()
                ->find(_data[i]["type"].asString())
                ->create(_entity, _data[i]["attributes"], _scene));
    }
}
