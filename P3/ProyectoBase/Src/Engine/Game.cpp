#include "Game.h"
#include "Scene.h"
#include "Loader.h"
#include "FactoriesFactory.h"
#include "OgreSDLContext.h"

#include <string>

Game::Game() {}


Game::~Game()
{
	delete scene;

	FactoriesFactory::getInstance()->clear();
	OgreSDLContext::getInstance()->erase();
}

void Game::initContext()
{
	OgreSDLContext::getInstance()->initApp("Test");
}

void Game::init(std::string _firstScene)
{
	initContext();
  
	Loader loader;
	loader.readScenes(scenesQueue);
  
	scene = new Scene();
	setScene(_firstScene);
}

void Game::update()
{
	while (!exit)
	{
		scene->update();
		exit = OgreSDLContext::getInstance()->renderLoop();
	}
}

void Game::setScene(std::string _sceneName)
{
	scene->clearComponentsManager();
	scene->clearEntities();
	scene->load(scenesQueue.find(_sceneName)->second);
}