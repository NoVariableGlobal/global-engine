#include "Game.h"
#include "Scene.h"
#include "Loader.h"
#include <string>
#include "FactoriesFactory.h"
#include "OgreSDLContext.h"

Game::Game() {}


Game::~Game()
{
	FactoriesFactory::getInstance()->clear();
	OgreSDLContext::getInstance()->erase();
	delete scene;
	scene = nullptr;
}

void Game::initContext()
{
	OgreSDLContext::getInstance()->initApp("Test");
}

void Game::init(std::string firstScene)
{
	initContext();
  
	Loader loader;
	loader.readScenes(scenesQueue);
  
	scene = new Scene();
	setScene(firstScene);

	update();
}

void Game::update()
{
	while (!exit)
	{
		scene->update();
		exit = OgreSDLContext::getInstance()->renderLoop();
	}
}

void Game::setScene(std::string sceneName)
{
	scene->load(scenesQueue.find(sceneName)->second);
}