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
    // We iterate from the size to 1, modifying `i` before we read it so the
    // range it reads is size - 1 to 0. This is also more efficient and safe as
    // it does not lose information by transforming a `size_t` into an `int`.
    auto i = physics_.size();
    while (i != 0) {
        delete physics_[--i];
        physics_.pop_back();
    }

    i = input_.size();
    while (i != 0) {
        delete input_[--i];
        input_.pop_back();
    }

    i = rend_.size();
    while (i != 0) {
        delete rend_[--i];
        rend_.pop_back();
    }

    i = sound_.size();
    while (i != 0) {
        delete sound_[--i];
        sound_.pop_back();
    }

    i = event_.size();
    while (i != 0) {
        delete event_[--i];
        event_.pop_back();
    }

    i = deleteable_.size();
    while (i != 0) {
        delete deleteable_[--i];
        deleteable_.pop_back();
    }

    i = listener_.size();
    while (i != 0) {
        delete listener_[--i];
        listener_.pop_back();
    }
}

void ComponentsManager::addPC(PhysicsComponent* physicsComponent) {
    insertPhysics_.push_back(physicsComponent);
}

void ComponentsManager::insertPC() {
    // We iterate from the size to 1, modifying `i` before we read it so the
    // range it reads is size - 1 to 0. This is also more efficient and safe as
    // it does not lose information by transforming a `size_t` into an `int`.
    auto i = insertPhysics_.size();
    while (i != 0) {
        physics_.push_back(insertPhysics_[--i]);
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
    // We iterate from the size to 1, modifying `i` before we read it so the
    // range it reads is size - 1 to 0. This is also more efficient and safe as
    // it does not lose information by transforming a `size_t` into an `int`.
    auto i = insertInput_.size();
    while (i != 0) {
        input_.push_back(insertInput_[--i]);
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
    // We iterate from the size to 1, modifying `i` before we read it so the
    // range it reads is size - 1 to 0. This is also more efficient and safe as
    // it does not lose information by transforming a `size_t` into an `int`.
    auto i = insertRend_.size();
    while (i != 0) {
        rend_.push_back(insertRend_[--i]);
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
    // We iterate from the size to 1, modifying `i` before we read it so the
    // range it reads is size - 1 to 0. This is also more efficient and safe as
    // it does not lose information by transforming a `size_t` into an `int`.
    auto i = insertSound_.size();
    while (i != 0) {
        sound_.push_back(insertSound_[--i]);
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
    // We iterate from the size to 1, modifying `i` before we read it so the
    // range it reads is size - 1 to 0. This is also more efficient and safe as
    // it does not lose information by transforming a `size_t` into an `int`.
    auto i = insertDeleteable_.size();
    while (i != 0) {
        deleteable_.push_back(insertDeleteable_[--i]);
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
    // We iterate from the size to 1, modifying `i` before we read it so the
    // range it reads is size - 1 to 0. This is also more efficient and safe as
    // it does not lose information by transforming a `size_t` into an `int`.
    auto i = insertEvent_.size();
    while (i != 0) {
        event_.push_back(insertEvent_[--i]);
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
    auto i = insertListener_.size();
    while (i != 0) {
        listener_.push_back(insertListener_[--i]);
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