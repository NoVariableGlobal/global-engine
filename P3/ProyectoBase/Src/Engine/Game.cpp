#include "Game.h"
#include "Scene.h"
#include "Loader.h"
#include <string>
#include "FactoriesFactory.h"
#include "OgreSDLContext.h"

#include <iostream>

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
	OgreSDLContext::getInstance()->initApp("Test");
}

bool Game::init(std::string _firstScene)
{
	try
	{
		initContext();

		Loader loader;
		loader.readScenes(scenesQueue);

		scene = new Scene();
		setScene(_firstScene);

		return true;
	}
	catch (std::exception & e)
	{
		throw std::exception("init error");
		return false;
	}
}

void Game::update()
{
	int i = 0;
	while (!exit)
	{
		scene->update();
		exit = OgreSDLContext::getInstance()->renderLoop();

		while (i <= 100) {
			i++;
			if (i == 99) {
				setScene("Game");
			}
		}
	}
}

void Game::setScene(std::string _sceneName)
{
	if (!scenesQueue[_sceneName].empty()) 
	{
		scene->clearComponentsManager();
		scene->clearEntities();
		scene->load(scenesQueue.find(_sceneName)->second);
	}
}
