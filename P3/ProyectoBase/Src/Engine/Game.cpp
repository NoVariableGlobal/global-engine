#include "Game.h"
#include "Scene.h"
#include "Loader.h"
#include <string>

Game::Game(std::string firtscene)
{
	//...
	initContext();
	//...
	initScenes();
	//...
	setScene(firtscene);
}

Game::~Game()
{
	currentScene = nullptr;
	/*for (int i = 0; i < scenesQueue.size(); i++)
	{
		delete scenesQueue[i];
		scenesQueue[i] = nullptr;
	}*/
}

void Game::initContext()
{
	//...
	ApplicationContext();
	//...
}

void Game::initScenes()
{
	Loader loader;
	loader.readScenes(scenesQueue);
}

void Game::update()
{
	while (!exit)
	{
		currentScene->update();
	}
}

void Game::setScene(std::string scene)
{	
	currentScene->load(scene);
}