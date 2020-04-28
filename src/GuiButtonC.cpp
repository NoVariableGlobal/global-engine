#include "GuiButtonC.h"
#include "Entity.h"
#include "GuiContext.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>

CEGUI::Window* GuiButtonComponent::create(const std::string& text,
                                          const glm::vec2 position,
                                          const glm::vec2 size,
                                          const std::string& name) {
    CEGUI::Window* button =
        GuiContext::getInstance()->createButton(text, position, size, name);

    return button;
}
