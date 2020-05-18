#pragma once

#include <Ogre.h>
#include <SDL_events.h>
#include <glm/glm.hpp>
#include <string>

namespace CEGUI {
    class WindowManager;
    class OgreRenderer;
    class GUIContext;
    class Window;
    enum MouseButton;
} // namespace CEGUI

class GuiContext : public Ogre::FrameListener {
    static GuiContext* instance_;
    std::string schemeName_;

    Ogre::RenderWindow* mWindow_ = nullptr;
    CEGUI::OgreRenderer* mRenderer_ = nullptr;
    Ogre::Root* mRoot_ = nullptr;
    CEGUI::GUIContext* mContext_ = nullptr;

    CEGUI::Window* sheet_ = nullptr;
    CEGUI::WindowManager* mWindowManager_ = nullptr;

    GuiContext();

  public:
    static GuiContext* getInstance();

    static void init();
    void destroy();

    void captureInput(const SDL_Event& event);

    void loadScheme(const std::string& schemeName,
                    const std::string& schemeFile);

    void setFont(const std::string& fontFile);

    CEGUI::Window* createButton(const std::string& text, glm::vec2 position,
                                glm::vec2 size, const std::string& name);

    CEGUI::Window* createSlider(glm::vec2 position,
                                glm::vec2 size, const std::string& name);

    CEGUI::Window* createLabel(const std::string& text, glm::vec2 position,
                               glm::vec2 size, const std::string& name = "");

    CEGUI::Window* createImage(const std::string& image, glm::vec2 position,
                               glm::vec2 size, const std::string& name = "");

    static void setWidgetDestRect(CEGUI::Window* widget, glm::vec2 position,
                                  glm::vec2 size);

    void setMouseImage(const std::string& imageFile);

    void setMouseVisibility(bool b);

    void createFrameListener();

    void windowResized(Ogre::RenderWindow* rw);

    // Getters and setters
    CEGUI::OgreRenderer* getRenderer() const;
    CEGUI::GUIContext* getContext() const;
};