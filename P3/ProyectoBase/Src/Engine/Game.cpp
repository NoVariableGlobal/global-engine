#include "Game.h"
#include "Scene.h"
#include <string>

Game::Game()
{
	//...
	initContext();
	//...
	initScenes();
	//...

	// TODO: TEST - REMOVE BEFORE MERGING
	//setScene(new Scene());
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
	// TODO: TEST - REMOVE BEFORE MERGING
	//currentScene = scene;
	//currentScene->load();
}