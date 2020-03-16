#pragma once
#include <string>
#include <map>
#include "checkML.h"

class Scene;
class Loader;

class Game
{
	private:
		// Save <scene name, scene file>
		std::map<std::string, std::string> scenesQueue;
		Scene* scene = nullptr;

		bool exit = false;
		bool end = false;
		bool win = false;

	public:
		Game();
		~Game();

		/*
		* Inicializa el contexto de Ogre
		*/
		void initContext();
		/*
		* Inicializa el juego
		*/
		bool init(std::string _firstScene);
		/*
		* Maneja el bucle del juego
		*/
		void update();
		/*
		* Cambia la escena actual por la nueva
		*/
		void setScene(std::string _sceneName);
};
