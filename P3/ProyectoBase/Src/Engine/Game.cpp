#include "Game.h"
#include "Scene.h"
#include "Loader.h"
#include <string>
#include "FactoriesFactory.h"
#include "OgreSDLContext.h"
#include "PhysicsContext.h"

Game::Game() {}


Game::~Game()
{
	delete scene;
	scene = nullptr;
	FactoriesFactory::getInstance()->clear();
	OgreSDLContext::getInstance()->erase();
}

void Game::initContext()
{
	FactoriesFactory::init();
	OgreSDLContext::init();
	PhysicsContext::init();
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
	scene->load(scenesQueue.find(_sceneName)->second);
}