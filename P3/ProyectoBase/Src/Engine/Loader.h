#pragma once
#include <string>
#include <map>

class Entity;

class Loader
{
	public:
		Loader();
		~Loader();
		
		void readScenes(std::map<std::string, std::string>& scenesQueue);
		void readEntities(std::string file, std::map<std::string*, Entity*>& entities);
};