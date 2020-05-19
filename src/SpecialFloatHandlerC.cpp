#include "SpecialFloatHandlerC.h"


#include "ComponentsManager.h"
#include "Scene.h"


void SpecialFloatHandlerComponent::destroy() {
    scene_->getComponentsManager()->eraseDC(this);
}
