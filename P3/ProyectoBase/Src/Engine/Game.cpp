#include "Game.h"
#include "ApplicationContext.h"
#include "Scene.h"
#include <string>

Game::Game()
{
	//...
	initContext();
	//...
	initScenes();
	//...
}

Game::~Game()
{
	//...
	currentScene = nullptr;
	for (int i = 0; i < scenesQueue.size(); i++)
	{
		// delete scenesQueue[i];
		// scenesQueue[i] = nullptr;
	}
	//...
}

void Game::initContext()
{
	//...
	ApplicationContext();
	//...
}

void Game::initScenes()
{
	//...
}

void Game::update()
{
	//...
	while (!exit)
	{
		//...
		//currentScene.update();
		//...
	}
	//...
}

void Game::setScene(std::string scene)
{
	//...
}