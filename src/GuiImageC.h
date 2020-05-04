#pragma once

#include "Component.h"
#include "Factory.h"
#include <glm/glm.hpp>
#include <string>

namespace CEGUI {
    class Window;
}

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(GuiImageComponent);

class GuiImageComponent : public Component {
  protected:
    CEGUI::Window* myself;

    std::string image;
    glm::vec2 position;
    glm::vec2 size;
    std::string name;

  public:
    void create();

    void destroy();

    // Getters
    CEGUI::Window* getWindow();

    // Setters
    void setImage(std::string t);
    void setPosition(glm::vec2 p);
    void setSize(glm::vec2 s);
    void setName(std::string n);
};
