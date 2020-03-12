#include "Game.h"
#include "Scene.h"
#include "Loader.h"
#include <string>
#include "FactoriesFactory.h"
#include "OgreSDLContext.h"

#include <fstream>

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
	try {
		scene->clearComponentsManager();
		if (true) { //////////////////////////////////////////////////////////////////////////////AQUI FALTA LA CONDICION PARA QUE LEA
			scene->load(scenesQueue.find(_sceneName)->second);
		}
		else {
			throw std::invalid_argument("Requested scene does not exist");
		}
	}
	catch (std::invalid_argument const& invArg) {
		printf(invArg.what());
		std::exit;
	}
}