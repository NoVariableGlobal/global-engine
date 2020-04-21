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
#include <CEGUI/CEGUI.h>

#include <SDL_events.h>
#include <string>

#include <iostream>

Game::Game() {
    mGui_ = nullptr;
    Loader loader;
    loader.readSounds();
}

// Deletes the scene and clears the constexts
Game::~Game() {
    delete scene_;
    mGui_->destroy();
    delete mGui_;

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
bool Game::init(const std::string firstScene) {
    try {
        initContext();

        Loader loader;
        loader.readScenes(scenesQueue_);

        scene_ = new Scene(this);
        setScene(firstScene);

        mGui_ = new GUI();
        try {
            mGui_->init("TaharezLook.scheme");
            mGui_->setMouseImage("TaharezLook/MouseArrow");
            mGui_->setFont("DejaVuSans-14");

            CEGUI::Window* quitButton =
                mGui_->createButton("QUIT", glm::vec2(0.0f, 0.0f),
                                    glm::vec2(100.0f, 30.0f), "TestButton");

            quitButton->subscribeEvent(
                CEGUI::PushButton::EventClicked,
                CEGUI::Event::Subscriber(&Game::quit, this));

            CEGUI::Window* editbox =
                mGui_->createLabel("Odio CeGUI", glm::vec2(0.5f, 0.0f),
                                   glm::vec2(100.0f, 50.0f), "Text");

        } catch (CEGUI::Exception& e) {
            auto* message = e.getMessage().c_str();
            throw std::exception(message);
        }

        return true;
    } catch (std::exception& e) {
        std::cout << "ERROR: " << e.what();
        return false;
    }
}

void Game::run() {
    while (!exit_) {
        update();
        handleInput();
        scene_->insertComponents();
        scene_->deleteComponents();
        mGui_->captureInput();
        render();

        if (sceneChange_)
            setScene(sceneToChange_);
    }
}

void Game::update() { scene_->update(); }

void Game::render() {
    scene_->render();
    OgreSDLContext::getInstance()->renderLoop();
}

void Game::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event) && !exit_) {
        scene_->handleInput(event);
        exit_ = OgreSDLContext::getInstance()->pollEvents(event);
    }
}

void Game::setChangeScene(const bool change, const std::string sceneName,
                          const bool deleteAll) {
    sceneChange_ = change;
    sceneToChange_ = sceneName;
    deleteAll_ = deleteAll;
}

void Game::setScene(const std::string sceneName) {
    if (!deleteAll_)
        scene_->clearNonPersistantEntities();
    else
        scene_->clearEntities();

    scene_->deleteComponents();

    scene_->load(assert_find(scenesQueue_, sceneName));

    sceneChange_ = false;
    deleteAll_ = false;
}

void Game::quit() { exit_ = true; }
