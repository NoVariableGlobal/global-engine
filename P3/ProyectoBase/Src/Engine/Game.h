#pragma once
#include <string>
#include "ApplicationContext.h"

class Scene;
class ComponentFactory;

class Game : public OgreBites::ApplicationContext
{
	private:
		//Guarda <nombre de la escena, fichero de la escena>
		std::map<std::string, std::string> scenesQueue;
		Scene* currentScene = nullptr;

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
		* Inicializar el mapa de escenas
		*/
		void initScenes();
		/*
		* Maneja el bucle del juego
		*/
		void update();
		/*
		* Cambia la escena actual por la nueva
		*/
		void setScene(std::string scene);
};