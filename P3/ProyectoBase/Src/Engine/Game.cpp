#include "Game.h"
#include "Scene.h"
#include "Loader.h"
#include <string>
#include "FactoriesFactory.h"
#include "OgreSDLContext.h"

// TEMPORARY - This should go in the games
#include "GUI.h"

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

	// TEMPORARY - This should go in the games
	m_gui->init("GUI");
	m_gui->loadScheme("TaharezLook.scheme");
	m_gui->setFont("DejaVuSans-10");
	m_gui->createWidget("TaharezLook/Button", glm::vec4(0.5f, 0.5f, 0.1f, 0.05f), glm::vec4(0.0f), "TestButton");
}

void Game::update()
{
	while (!exit)
	{
		scene->update();
		exit = OgreSDLContext::getInstance()->renderLoop();
	}

	// TEMPORARY - This should go in the games
	m_gui->draw();
}

void Game::setScene(std::string _sceneName)
{
	scene->clearComponentsManager();
	scene->load(scenesQueue.find(_sceneName)->second);
}