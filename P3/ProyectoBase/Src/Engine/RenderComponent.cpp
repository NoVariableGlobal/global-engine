#include "RenderComponent.h"
#include "OgreContext.h"

RenderComponent::RenderComponent() {
  mSM = OgreContext::instance()->getSceneManager();
}

RenderComponent::~RenderComponent() {}