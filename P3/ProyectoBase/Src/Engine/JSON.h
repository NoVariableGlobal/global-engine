#pragma once
#include <string>
#include <map>

class JSON
{
	public:
		JSON();
		~JSON();
		
		void readScenes(std::map<std::string, std::string>& scenesQueue);
		void readEntities(std::string file, std::map<Id*, Entity*>& entities);
};