#include "ComponentsManager.h"
#include "EventComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "SoundComponent.h"
#include "SoundContext.h"
#include "Util.h"

#include <SDL_events.h>
#include <iostream>

ComponentsManager::ComponentsManager() {}

ComponentsManager::~ComponentsManager() { clearComponents(); }

void ComponentsManager::clearComponents() {
    int size = physics.size();
    for (int i = size - 1; i >= 0; i--) {
        delete physics[i];
        physics.pop_back();
    }

    size = input.size();
    for (int i = size - 1; i >= 0; i--) {
        delete input[i];
        input.pop_back();
    }

    size = rend.size();
    for (int i = size - 1; i >= 0; i--) {
        delete rend[i];
        rend.pop_back();
    }

    size = sound.size();
    for (int i = size - 1; i >= 0; i--) {
        delete sound[i];
        sound.pop_back();
    }

    size = event.size();
    for (int i = size - 1; i >= 0; i--) {
        delete event[i];
        event.pop_back();
    }

    size = deleteable.size();
    for (int i = size - 1; i >= 0; i--) {
        delete deleteable[i];
        deleteable.pop_back();
    }
}

void ComponentsManager::addPC(PhysicsComponent* _physicsComponent) {
    insertPhysics.push_back(_physicsComponent);
}

void ComponentsManager::insertPC() {
    int size = insertPhysics.size();
    for (int i = size - 1; i >= 0; i--) {
        physics.push_back(insertPhysics[i]);
        insertPhysics.pop_back();
    }
}

void ComponentsManager::deletePC() {
    assert_deleteComponent(deletePhysics, physics);
}

void ComponentsManager::erasePC(PhysicsComponent* _physicsComponent) {
    deletePhysics.push_back(_physicsComponent);
}

void ComponentsManager::addIC(InputComponent* _inputComponent) {
    insertInput.push_back(_inputComponent);
}

void ComponentsManager::insertIC() {
    int size = insertInput.size();
    for (int i = size - 1; i >= 0; i--) {
        input.push_back(insertInput[i]);
        insertInput.pop_back();
    }
}

void ComponentsManager::deleteIC() {
    assert_deleteComponent(deleteInput, input);
}

void ComponentsManager::eraseIC(InputComponent* _inputComponent) {
    deleteInput.push_back(_inputComponent);
}

void ComponentsManager::addRC(RenderComponent* _renderComponent) {
    insertRend.push_back(_renderComponent);
}

void ComponentsManager::insertRC() {
    int size = insertRend.size();
    for (int i = size - 1; i >= 0; i--) {
        rend.push_back(insertRend[i]);
        insertRend.pop_back();
    }
}

void ComponentsManager::deleteRC() { assert_deleteComponent(deleteRend, rend); }

void ComponentsManager::eraseRC(RenderComponent* _renderComponent) {
    deleteRend.push_back(_renderComponent);
}

void ComponentsManager::addSC(SoundComponent* _soundComponent) {
    insertSound.push_back(_soundComponent);
}

void ComponentsManager::insertSC() {
    int size = insertSound.size();
    for (int i = size - 1; i >= 0; i--) {
        sound.push_back(insertSound[i]);
        insertSound.pop_back();
    }
}

void ComponentsManager::deleteSC() {
    assert_deleteComponent(deleteSound, sound);
}

void ComponentsManager::eraseSC(SoundComponent* _soundComponent) {
    deleteSound.push_back(_soundComponent);
}

void ComponentsManager::addDC(Component* _deleteableComponent) {
    insertDeleteable.push_back(_deleteableComponent);
}

void ComponentsManager::insertDC() {
    int size = insertDeleteable.size();
    for (int i = size - 1; i >= 0; i--) {
        deleteable.push_back(insertDeleteable[i]);
        insertDeleteable.pop_back();
    }
}

void ComponentsManager::deleteDC() {
    assert_deleteComponent(deleteDeleteable, deleteable);
}

void ComponentsManager::eraseDC(Component* _deleteableComponent) {
    deleteDeleteable.push_back(_deleteableComponent);
}

void ComponentsManager::addEC(EventComponent* _eventComponent) {
    insertEvent.push_back(_eventComponent);
}

void ComponentsManager::insertEC() {
    int size = insertEvent.size();
    for (int i = size - 1; i >= 0; i--) {
        event.push_back(insertEvent[i]);
        insertEvent.pop_back();
    }
}

void ComponentsManager::deleteEC() {
    assert_deleteComponent(deleteEvent, event);
}

void ComponentsManager::eraseEC(EventComponent* _eventComponent) {
    deleteEvent.push_back(_eventComponent);
}

void ComponentsManager::update() {
    for (auto p : physics) {
        if (p->isActive())
            p->update();
    }
}

void ComponentsManager::handleInput(const SDL_Event& _event) {
    for (auto i : input) {
        if (i->isActive())
            i->handleInput(_event);
    }
}

void ComponentsManager::render() {
    for (auto r : rend) {
        if (r->isActive())
            r->render();
    }
}

void ComponentsManager::updateSound() { SoundContext::getInstance()->update(); }

void ComponentsManager::updateEvent() {
    for (auto e : event) {
        if (e->isActive())
            e->checkEvent();
    }
}

void ComponentsManager::deleteComponents() {
    deletePC();
    deleteIC();
    deleteRC();
    deleteSC();
    deleteDC();
    deleteEC();
}
void ComponentsManager::insertComponents() {
    insertPC();
    insertIC();
    insertRC();
    insertSC();
    insertDC();
    insertEC();
}