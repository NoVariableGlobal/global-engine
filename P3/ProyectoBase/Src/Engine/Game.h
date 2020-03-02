#pragma once
#include <string>
#include "ApplicationContext.h"

class Scene;
class Loader;

class Game : public OgreBites::ApplicationContext
{
	private:
		// Save <scene name, scene file>
		std::map<std::string, std::string> scenesQueue;
		Scene* scene = nullptr;

		bool exit = false;
		bool end = false;
		bool win = false;

	public:
		Game(std::string firtscene);
		~Game();

		/*
		* Inicializa el contexto de Ogre
		*/
		void initContext();
		/*
		* Inicializa el juego
		*/
		void init(std::string firstScene);
		/*
		* Maneja el bucle del juego
		*/
		void update();
		/*
		* Cambia la escena actual por la nueva
		*/
		void setScene(std::string scene);
};
