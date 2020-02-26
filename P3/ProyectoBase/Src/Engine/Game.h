#include <string>
#include <map>
#include "ApplicationContext.h"

class Scene;



class ComponentFactory
{
	public:
		ComponentFactory() {};
};

std::map<std::string, ComponentFactory*> factory;



class Game : public OgreBites::ApplicationContext
{
	private:
		std::map<std::string, std::string> scenesQueue;
		Scene* currentScene = nullptr;

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