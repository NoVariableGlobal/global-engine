#include "Loader.h"
#include "Entity.h"

#include <json.h>
#include <fstream>

Loader::Loader()
{
}

Loader::~Loader()
{
}

void Loader::readScenes(std::map<std::string, std::string>& scenesQueue)
{
}

void Loader::readEntities(std::string file, std::map<std::string*, Entity*>& entities)
{
	Json::Value root;
	std::ifstream fileStream(file);
	fileStream >> root;
}
