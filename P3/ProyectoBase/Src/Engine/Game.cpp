#include "Game.h"
#include "Scene.h"
#include "Loader.h"
#include "FactoriesFactory.h"
#include "OgreSDLContext.h"

#include <string>

#include <SDL_events.h>

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

void Game::run()
{
	while (!exit)
	{
		update();
		render();
		handleInput();
	}

}

void Game::update()
{
	scene->update();
}

void Game::render()
{
	OgreSDLContext::getInstance()->renderLoop();
	scene->render();
}

void Game::handleInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit)
	{
		scene->handleInput(event);
		exit = OgreSDLContext::getInstance()->pollEvents(event);
	}
}

void Game::setScene(std::string _sceneName)
{
	scene->clearComponentsManager();
	scene->load(scenesQueue.find(_sceneName)->second);
}