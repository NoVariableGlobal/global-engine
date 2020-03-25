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
    if (deletePhysics.size() > 0) {
        bool erased = false;
        auto itDelete = deletePhysics.begin();
        while (itDelete != deletePhysics.end()) {
            auto it = physics.begin();
            while (it != physics.end() && !erased) {
                if ((*it) == (*itDelete)) {
                    delete *it;
                    erased = true;
                } else
                    ++it;
            }
            physics.erase(it);
            ++itDelete;
        }
        deletePhysics.clear();
    }
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
    if (deleteInput.size() > 0) {
        bool erased = false;
        auto itDelete = deleteInput.begin();
        while (itDelete != deleteInput.end()) {
            auto it = input.begin();
            while (it != input.end() && !erased) {
                if ((*it) == (*itDelete)) {
                    delete *it;
                    erased = true;
                } else
                    ++it;
            }
            input.erase(it);
            ++itDelete;
        }
        deleteInput.clear();
    }
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

void ComponentsManager::deleteRC() {
    if (deleteRend.size() > 0) {
        bool erased = false;
        auto itDelete = deleteRend.begin();
        while (itDelete != deleteRend.end()) {
            auto it = rend.begin();
            while (it != rend.end() && !erased) {
                if ((*it) == (*itDelete)) {
                    delete *it;
                    erased = true;
                } else
                    ++it;
            }
            rend.erase(it);
            ++itDelete;
        }
        deleteRend.clear();
    }
}

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
    if (deleteSound.size() > 0) {
        bool erased = false;
        auto itDelete = deleteSound.begin();
        while (itDelete != deleteSound.end()) {
            auto it = sound.begin();
            while (it != sound.end() && !erased) {
                if ((*it) == (*itDelete)) {
                    delete *it;
                    erased = true;
                } else
                    ++it;
            }
            sound.erase(it);
            ++itDelete;
        }
        deleteSound.clear();
    }
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
    if (deleteDeleteable.size() > 0) {
        bool erased = false;
        auto itDelete = deleteDeleteable.begin();
        while (itDelete != deleteDeleteable.end()) {
            auto it = deleteable.begin();
            while (it != deleteable.end() && !erased) {
                if ((*it) == (*itDelete)) {
                    delete *it;
                    erased = true;
                } else
                    ++it;
            }
            deleteable.erase(it);
            ++itDelete;
        }
        deleteDeleteable.clear();
    }
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
    if (deleteEvent.size() > 0) {
        bool erased = false;
        auto itDelete = deleteEvent.begin();
        while (itDelete != deleteEvent.end()) {
            auto it = event.begin();
            while (it != event.end() && !erased) {
                if ((*it) == (*itDelete)) {
                    delete *it;
                    erased = true;
                } else
                    ++it;
            }
            event.erase(it);
            ++itDelete;
        }
        deleteEvent.clear();
    }
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

void ComponentsManager::updateSound() {
    // TODO: updateSound method in SoundComponent
    /* for (auto s : sound){
        if (s->isActive())
            s->updateSound()
            }*/
}

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