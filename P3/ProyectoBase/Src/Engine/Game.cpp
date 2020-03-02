#include "Game.h"
#include "Scene.h"
#include "Loader.h"
#include "ComponentsManager.h"
#include <string>

Game::Game() { }

Game::~Game()
{
	currentScene = nullptr;
	componentsManager = nullptr;

	for (auto it = scenesQueue.begin; it != scenesQueue.end; it++) {
		delete *it;
		it = nullptr;
	}
}

void Game::initContext()
{
	ApplicationContext();
}

void Game::init(std::string firstScene)
{
	loader = new Loader();

	initContext();

	componentsManager = new ComponentsManager();
	setScene(firstScene);
}

void Game::update()
{
	while (!exit)
	{
		currentScene->update();
		componentsManager->update();
		componentsManager->handleInput();
		componentsManager->updateSound();
		componentsManager->updateCamera();
	}
}

void Game::setScene(std::string scene)
{	
	componentsManager->clearComponents();

	loader->readScenes(scenesQueue);

	currentScene->load(scene);
}
