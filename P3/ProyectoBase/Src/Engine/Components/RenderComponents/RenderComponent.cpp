#include "RenderComponent.h"
#include "../../Core/OgreContext.h"

RenderComponent::RenderComponent() {
  mSM = OgreContext::instance()->getSceneManager();
}

RenderComponent::~RenderComponent() {}