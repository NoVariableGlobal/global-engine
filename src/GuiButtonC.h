#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <string>

namespace CEGUI {
    class Window;
}

class GuiButtonComponent : public Component {
  public:
    CEGUI::Window* create(const std::string& text, const glm::vec2 position,
                          const glm::vec2 size, const std::string& name);
    virtual void onClick() = 0;
};
