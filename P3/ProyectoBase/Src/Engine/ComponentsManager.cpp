#include "ComponentsManager.h"
#include "EventComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "SoundComponent.h"

#include <SDL_events.h>

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
    physics.push_back(_physicsComponent);
}

void ComponentsManager::deletePC() {
    if (deletePhysics.size() > 0) {
        bool erased = false;
        auto itDelete = deletePhysics.begin();
        while (itDelete != deletePhysics.end()) {
            auto it = physics.begin();
            while (it != physics.end() && !erased) {
                if ((*it) == (*itDelete)) {
                    physics.erase(it);
                    erased = true;
                }
                ++it;
            }
            ++itDelete;
        }
    }
}

void ComponentsManager::erasePC(PhysicsComponent* _physicsComponent) {
    deletePhysics.push_back(_physicsComponent);
}

void ComponentsManager::addIC(InputComponent* _inputComponent) {
    input.push_back(_inputComponent);
}

void ComponentsManager::deleteIC() {
    if (deleteInput.size() > 0) {
        bool erased = false;
        auto itDelete = deleteInput.begin();
        while (itDelete != deleteInput.end()) {
            auto it = input.begin();
            while (it != input.end() && !erased) {
                if ((*it) == (*itDelete)) {
                    input.erase(it);
                    erased = true;
                }
                ++it;
            }
            ++itDelete;
        }
    }
}

void ComponentsManager::eraseIC(InputComponent* _inputComponent) {
    deleteInput.push_back(_inputComponent);
}

void ComponentsManager::addRC(RenderComponent* _renderComponent) {
    rend.push_back(_renderComponent);
}

void ComponentsManager::deleteRC() {
    if (deleteRend.size() > 0) {
        bool erased = false;
        auto itDelete = deleteRend.begin();
        while (itDelete != deleteRend.end()) {
            auto it = rend.begin();
            while (it != rend.end() && !erased) {
                if ((*it) == (*itDelete)) {
                    rend.erase(it);
                    erased = true;
                }
                ++it;
            }
            ++itDelete;
        }
    }
}

void ComponentsManager::eraseRC(RenderComponent* _renderComponent) {
    deleteRend.push_back(_renderComponent);
}

void ComponentsManager::addSC(SoundComponent* _soundComponent) {
    sound.push_back(_soundComponent);
}

void ComponentsManager::deleteSC() {
    if (deleteSound.size() > 0) {
        bool erased = false;
        auto itDelete = deleteSound.begin();
        while (itDelete != deleteSound.end()) {
            auto it = sound.begin();
            while (it != sound.end() && !erased) {
                if ((*it) == (*itDelete)) {
                    sound.erase(it);
                    erased = true;
                }
                ++it;
            }
            ++itDelete;
        }
    }
}

void ComponentsManager::eraseSC(SoundComponent* _soundComponent) {
    deleteSound.push_back(_soundComponent);
}

void ComponentsManager::addDC(Component* _deleteableComponent) {
    deleteable.push_back(_deleteableComponent);
}

void ComponentsManager::deleteDC() {
    if (deleteDeleteable.size() > 0) {
        bool erased = false;
        auto itDelete = deleteDeleteable.begin();
        while (itDelete != deleteDeleteable.end()) {
            auto it = deleteable.begin();
            while (it != deleteable.end() && !erased) {
                if ((*it) == (*itDelete)) {
                    deleteable.erase(it);
                    erased = true;
                }
                ++it;
            }
            ++itDelete;
        }
    }
}

void ComponentsManager::eraseDC(Component* _deleteableComponent) {
    deleteDeleteable.push_back(_deleteableComponent);
}

void ComponentsManager::addEC(EventComponent* _eventComponent) {
    event.push_back(_eventComponent);
}

void ComponentsManager::deleteEC() {
    if (deleteEvent.size() > 0) {
        bool erased = false;
        auto itDelete = deleteEvent.begin();
        while (itDelete != deleteEvent.end()) {
            auto it = event.begin();
            while (it != event.end() && !erased) {
                if ((*it) == (*itDelete)) {
                    event.erase(it);
                    erased = true;
                }
                ++it;
            }
            ++itDelete;
        }
    }
}

void ComponentsManager::eraseEC(EventComponent* _eventComponent) {
    deleteEvent.push_back(_eventComponent);
}

void ComponentsManager::update() {
    for (auto p : physics)
        p->update();
}

void ComponentsManager::handleInput(const SDL_Event& _event) {
    for (auto i : input)
        i->handleInput(_event);
}

void ComponentsManager::render() {
    for (auto r : rend)
        r->render();
}

void ComponentsManager::updateSound() {
    // TODO: updateSound method in SoundComponent
    /* for (auto s : sound)
            s->updateSound() */
}

void ComponentsManager::updateEvent() {
    for (auto r : event)
        r->checkEvent();
}

void ComponentsManager::deleteComponents() {
    deletePC();
    deleteIC();
    deleteRC();
    deleteSC();
    deleteDC();
    deleteEC();
}
