#include <string>
#include <map>
#include "ApplicationContext.h"

class Scene;
class ComponentsManager;
class Loader;

class Game : public OgreBites::ApplicationContext
{
	private:
		std::map<std::string, std::string> scenesQueue;
		Scene* currentScene = nullptr;

		// to manage the game
		ComponentsManager* componentsManager;
		Loader* loader;

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
