#pragma once

#include "Component.h"
#include "Factory.h"
#include <glm/glm.hpp>
#include <string>

namespace CEGUI {
    class Window;
}

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(GuiLabelComponent);

class GuiLabelComponent final : public Component {
  private:
    CEGUI::Window* myself;

    std::string text;
    glm::vec2 position;
    glm::vec2 size;
    std::string name;

  public:
    void create();

    void destroy();

    // Setters
    void setText(std::string t);
    void setPosition(glm::vec2 p);
    void setSize(glm::vec2 s);
    void setName(std::string n);
};
