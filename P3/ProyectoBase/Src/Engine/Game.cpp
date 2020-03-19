#include "Game.h"
#include "Scene.h"
#include "Loader.h"
#include "FactoriesFactory.h"
#include "OgreSDLContext.h"
#include "PhysicsContext.h"

#include <string>
#include <SDL_events.h>

#include <iostream>

Game::Game() {}

//Deletes the scene and clears the constexts
Game::~Game()
{
	delete scene;

	FactoriesFactory::getInstance()->clear();
	OgreSDLContext::getInstance()->erase();
}

//Inits all context
void Game::initContext()
{
	OgreSDLContext::init();
	PhysicsContext::init();
	OgreSDLContext::getInstance()->initApp("Test");
}
//Reads the scenes and sets the first one
bool Game::init(std::string _firstScene)
{
	try
	{
		initContext();

		Loader loader;
		loader.readScenes(scenesQueue);

		scene = new Scene(this);
		setScene(_firstScene);

		return true;
	}
	catch (std::exception & e)
	{
		std::cout << "init ERROR: " << e.what();
		return false;
	}
}

void Game::run()
{
	int i = 0;
	while (!exit)
	{
		update();
		render();
		handleInput();

		if (sceneChange)
			setScene(sceneToChange);
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

void Game::setChangeScene(bool _change, std::string _sceneName) 
{
	sceneChange = _change; 
	sceneToChange = _sceneName;
}

void Game::setScene(std::string _sceneName)
{
	scene->clearComponentsManager();
	scene->clearEntities();
	PhysicsContext::getInstance()->destroyWorldContent();

	scene->load(scenesQueue.find(_sceneName)->second);

	sceneChange = false;
}