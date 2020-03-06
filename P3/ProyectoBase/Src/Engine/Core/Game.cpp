#include "Game.h"
#include "Scene.h"
#include "../Managers/Loader.h"
#include <string>

Game::Game() { }


Game::~Game()
{
  delete scene;
	scene = nullptr;
}

void Game::initContext()
{
	//...
	//ApplicationContext();
	//...
}

void Game::init(std::string firstScene)
{
  initContext();
  
	Loader loader;
	loader.readScenes(scenesQueue);
  
  scene = new Scene();
	setScene(firstScene);
}

void Game::update()
{
	while (!exit)
	{
		scene->update();
	}
}

void Game::setScene(std::string sceneName)
{
	scene->load(scenesQueue.find(sceneName)->second);
}