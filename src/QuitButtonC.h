#pragma once

#include "Factory.h"
#include "GuiButtonC.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(QuitButtonComponent);

class QuitButtonComponent final : public GuiButtonComponent {
  private:
    std::string text;
    glm::vec2 position;
    glm::vec2 size;
    std::string name;

  public:
    void create();

    virtual void onClick();

    void destroy();

    // Setters
    void setText(std::string t);
    void setPosition(glm::vec2 p);
    void setSize(glm::vec2 s);
    void setName(std::string n);
};
