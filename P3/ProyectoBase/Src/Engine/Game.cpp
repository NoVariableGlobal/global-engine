#include "Game.h"
#include "ApplicationContext.h"
#include "ComponentsManager.h"
#include "Scene.h"
#include <string>

Game::Game()
{
	//...
	initContext();
	//...
	initScenes();
	//...
	componentsManager = new ComponentsManager();
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
		//currentScene->update();
		componentsManager->update();
		componentsManager->handleInput();
		componentsManager->updateSound();
		componentsManager->updateCamera();
		//...
	}
	//...
}

void Game::setScene(std::string scene)
{	
	componentsManager->clearComponents();
	
	currentScene->load(scene);
	//...
}
