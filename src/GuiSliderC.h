#pragma once

#include "Component.h"
#include "Factory.h"
#include <glm/glm.hpp>
#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(GuiSliderComponent);

namespace CEGUI {
    class Slider;
    class SubscriberSlot;
    class String;
}

class GuiSliderComponent : public Component {
  protected:
    CEGUI::Slider* myself = nullptr;

  public:
    CEGUI::Slider* create(const glm::vec2 position,
                          const glm::vec2 size, const std::string& name);

    void subscribeEvent(const CEGUI::String& event, CEGUI::SubscriberSlot  subscriber);
    float getValue();

    virtual void destroy();
    //virtual void onClick() = 0;
};
