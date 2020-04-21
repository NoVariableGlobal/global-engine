#include "ComponentsManager.h"
#include "AnimationLC.h"
#include "EventComponent.h"
#include "InputComponent.h"
#include "OgreSDLContext.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "SoundComponent.h"
#include "SoundContext.h"
#include "Util.h"

#include <Ogre.h>

ComponentsManager::ComponentsManager() {
    OgreSDLContext::getInstance()->getRoot()->addFrameListener(this);
}

ComponentsManager::~ComponentsManager() { clearComponents(); }

void ComponentsManager::clearComponents() {
    int size = physics_.size();
    for (int i = size - 1; i >= 0; i--) {
        delete physics_[i];
        physics_.pop_back();
    }

    size = input_.size();
    for (int i = size - 1; i >= 0; i--) {
        delete input_[i];
        input_.pop_back();
    }

    size = rend_.size();
    for (int i = size - 1; i >= 0; i--) {
        delete rend_[i];
        rend_.pop_back();
    }

    size = sound_.size();
    for (int i = size - 1; i >= 0; i--) {
        delete sound_[i];
        sound_.pop_back();
    }

    size = event_.size();
    for (int i = size - 1; i >= 0; i--) {
        delete event_[i];
        event_.pop_back();
    }

    size = deleteable_.size();
    for (int i = size - 1; i >= 0; i--) {
        delete deleteable_[i];
        deleteable_.pop_back();
    }

    size = listener_.size();
    for (int i = size - 1; i >= 0; i--) {
        delete listener_[i];
        listener_.pop_back();
    }
}

void ComponentsManager::addPC(PhysicsComponent* physicsComponent) {
    insertPhysics_.push_back(physicsComponent);
}

void ComponentsManager::insertPC() {
    const int size = insertPhysics_.size();
    for (int i = size - 1; i >= 0; i--) {
        physics_.push_back(insertPhysics_[i]);
        insertPhysics_.pop_back();
    }
}

void ComponentsManager::deletePC() {
    assert_deleteComponent(deletePhysics_, physics_);
}

void ComponentsManager::erasePC(PhysicsComponent* physicsComponent) {
    deletePhysics_.push_back(physicsComponent);
}

void ComponentsManager::addIC(InputComponent* inputComponent) {
    insertInput_.push_back(inputComponent);
}

void ComponentsManager::insertIC() {
    const int size = insertInput_.size();
    for (int i = size - 1; i >= 0; i--) {
        input_.push_back(insertInput_[i]);
        insertInput_.pop_back();
    }
}

void ComponentsManager::deleteIC() {
    assert_deleteComponent(deleteInput_, input_);
}

void ComponentsManager::eraseIC(InputComponent* inputComponent) {
    deleteInput_.push_back(inputComponent);
}

void ComponentsManager::addRC(RenderComponent* renderComponent) {
    insertRend_.push_back(renderComponent);
}

void ComponentsManager::insertRC() {
    const int size = insertRend_.size();
    for (int i = size - 1; i >= 0; i--) {
        rend_.push_back(insertRend_[i]);
        insertRend_.pop_back();
    }
}

void ComponentsManager::deleteRC() {
    assert_deleteComponent(deleteRend_, rend_);
}

void ComponentsManager::eraseRC(RenderComponent* renderComponent) {
    deleteRend_.push_back(renderComponent);
}

void ComponentsManager::addSC(SoundComponent* soundComponent) {
    insertSound_.push_back(soundComponent);
}

void ComponentsManager::insertSC() {
    const int size = insertSound_.size();
    for (int i = size - 1; i >= 0; i--) {
        sound_.push_back(insertSound_[i]);
        insertSound_.pop_back();
    }
}

void ComponentsManager::deleteSC() {
    assert_deleteComponent(deleteSound_, sound_);
}

void ComponentsManager::eraseSC(SoundComponent* soundComponent) {
    deleteSound_.push_back(soundComponent);
}

void ComponentsManager::addDC(Component* deleteableComponent) {
    insertDeleteable_.push_back(deleteableComponent);
}

void ComponentsManager::insertDC() {
    const int size = insertDeleteable_.size();
    for (int i = size - 1; i >= 0; i--) {
        deleteable_.push_back(insertDeleteable_[i]);
        insertDeleteable_.pop_back();
    }
}

void ComponentsManager::deleteDC() {
    assert_deleteComponent(deleteDeleteable_, deleteable_);
}

void ComponentsManager::eraseDC(Component* deleteableComponent) {
    deleteDeleteable_.push_back(deleteableComponent);
}

void ComponentsManager::addEC(EventComponent* eventComponent) {
    insertEvent_.push_back(eventComponent);
}

void ComponentsManager::insertEC() {
    const int size = insertEvent_.size();
    for (int i = size - 1; i >= 0; i--) {
        event_.push_back(insertEvent_[i]);
        insertEvent_.pop_back();
    }
}

void ComponentsManager::deleteEC() {
    assert_deleteComponent(deleteEvent_, event_);
}

void ComponentsManager::eraseEC(EventComponent* eventComponent) {
    deleteEvent_.push_back(eventComponent);
}

void ComponentsManager::addLC(ListenerComponent* listenerComponent) {
    insertListener_.push_back(listenerComponent);
}

void ComponentsManager::insertLC() {
    const int size = insertListener_.size();
    for (int i = size - 1; i >= 0; i--) {
        listener_.push_back(insertListener_[i]);
        insertListener_.pop_back();
    }
}

void ComponentsManager::deleteLC() {
    assert_deleteComponent(deleteListener_, listener_);
}

void ComponentsManager::eraseLC(ListenerComponent* listenerComponent) {
    deleteListener_.push_back(listenerComponent);
}

void ComponentsManager::update() {
    for (auto p : physics_) {
        if (p->isActive())
            p->update();
    }
}

void ComponentsManager::handleInput(const SDL_Event& event) {
    for (auto i : input_) {
        if (i->isActive())
            i->handleInput(event);
    }
}

void ComponentsManager::render() {
    for (auto r : rend_) {
        if (r->isActive())
            r->render();
    }
}

void ComponentsManager::updateSound() { SoundContext::getInstance()->update(); }

void ComponentsManager::updateEvent() {
    for (auto e : event_) {
        if (e->isActive())
            e->checkEvent();
    }
}

bool ComponentsManager::frameRenderingQueued(const Ogre::FrameEvent& _event) {
    for (auto l : listener_) {
        if (l->isActive())
            l->frameRendered(_event);
    }

    return true;
}

void ComponentsManager::deleteComponents() {
    deletePC();
    deleteIC();
    deleteRC();
    deleteSC();
    deleteDC();
    deleteEC();
    deleteLC();
}

void ComponentsManager::insertComponents() {
    insertPC();
    insertIC();
    insertRC();
    insertSC();
    insertDC();
    insertEC();
    insertLC();
}