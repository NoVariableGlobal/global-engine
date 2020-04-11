#include "Game.h"
#include "AnimationLC.h"
#include "CameraRC.h"
#include "FactoriesFactory.h"
#include "GUI.h"
#include "Loader.h"
#include "OgreSDLContext.h"
#include "PhysicsContext.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "SleepEC.h"
#include "SoundComponent.h"
#include "SoundContext.h"
#include "SoundListenerComponent.h"
#include "SpotLightRC.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"
#include "Util.h"

#include <SDL_events.h>
#include <string>

#include <iostream>

Game::Game() {
    Loader loader;
    loader.readSounds();
}

// Deletes the scene and clears the constexts
Game::~Game() {
    delete scene;

    FactoriesFactory::getInstance()->clear();
    OgreSDLContext::getInstance()->erase();
    SoundContext::destroy();
}

// Inits all context
void Game::initContext() {
    OgreSDLContext::init();
    PhysicsContext::init();
    OgreSDLContext::getInstance()->initApp("Test");
    SoundContext::getInstance()->init();

    TransformComponentFactoryRegisterGlobalVar.noop();
    RigidbodyPCFactoryRegisterGlobalVar.noop();
    CameraRCFactoryRegisterGlobalVar.noop();
    SpotLightRCFactoryRegisterGlobalVar.noop();
    TridimensionalObjectRCFactoryRegisterGlobalVar.noop();
    SoundComponentFactoryRegisterGlobalVar.noop();
    SoundListenerComponentFactoryRegisterGlobalVar.noop();
    SleepECFactoryRegisterGlobalVar.noop();
    AnimationLCFactoryRegisterGlobalVar.noop();
}

// Reads the scenes and sets the first one
bool Game::init(std::string _firstScene) {
    try {
        initContext();

        Loader loader;
        loader.readScenes(scenesQueue);

        scene = new Scene(this);
        setScene(_firstScene);

        m_gui = new GUI();
        try {
            m_gui->init("GUI");
            m_gui->loadScheme("TaharezLook.scheme");
            m_gui->setFont("DejaVuSans-10");

            CEGUI::PushButton* testButton =
                static_cast<CEGUI::PushButton*>(m_gui->createWidget(
                    "TaharezLook/Button", glm::vec4(0.5f, 0.5f, 0.1f, 0.05f),
                    glm::vec4(0.0f), "TestButton"));
            testButton->setText("Hello World!");

        } catch (CEGUI::Exception& e) {
            auto message = e.getMessage().c_str();
            throw std::exception(message);
        }

        return true;
    } catch (std::exception& e) {
        std::cout << "init ERROR: " << e.what();
        return false;
    }
}

void Game::run() {
    while (!exit) {
        update();
        handleInput();
        scene->insertComponents();
        scene->deleteComponents();
        render();

        if (sceneChange)
            setScene(sceneToChange);
    }
}

void Game::update() { scene->update(); }

void Game::render() {
    scene->render();
    OgreSDLContext::getInstance()->renderLoop();
}

void Game::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event) && !exit) {
        scene->handleInput(event);
        exit = OgreSDLContext::getInstance()->pollEvents(event);
    }
}

void Game::setChangeScene(bool _change, std::string _sceneName,
                          bool _deleteAll) {
    sceneChange = _change;
    sceneToChange = _sceneName;
    deleteAll = _deleteAll;
}

void Game::setScene(std::string _sceneName) {
    if (!deleteAll)
        scene->clearNonPersistantEntities();
    else
        scene->clearEntities();

    scene->deleteComponents();

    scene->load(assert_find(scenesQueue, _sceneName));

    sceneChange = false;
    deleteAll = false;
}