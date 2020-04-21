#pragma once

#include "OISKeyboard.h"
#include "OISMouse.h"
#include <Ogre.h>
#include <glm/glm.hpp>
#include <string>

namespace CEGUI {
    class WindowManager;
    class OgreRenderer;
    class GUIContext;
    class Window;
    enum MouseButton;
} // namespace CEGUI

namespace OIS {
    class InputManager;
    class Keyboard;
    class Mouse;
} // namespace OIS

class GUI final : public OIS::KeyListener,
                  public OIS::MouseListener,
                  public Ogre::FrameListener {
    Ogre::RenderWindow* mWindow_ = nullptr;
    CEGUI::OgreRenderer* mRenderer_ = nullptr;
    Ogre::Root* mRoot_ = nullptr;
    CEGUI::GUIContext* mContext_ = nullptr;

    CEGUI::Window* sheet_ = nullptr;
    CEGUI::WindowManager* mWindowManager_ = nullptr;

    OIS::InputManager* mInputManager_ = nullptr;
    OIS::Mouse* mMouse_ = nullptr;
    OIS::Keyboard* mKeyboard_ = nullptr;

  public:
    void init(std::string scheme);
    void destroy();
    void draw();

    void loadScheme(const std::string& schemeFile);

    void setFont(const std::string& fontFile);

    CEGUI::Window* createButton(const std::string& text, glm::vec2 position,
                                glm::vec2 size, const std::string& name);

    CEGUI::Window* createLabel(const std::string& text, glm::vec2 position,
                               glm::vec2 size, const std::string& name = "");

    static void setWidgetDestRect(CEGUI::Window* widget, glm::vec2 position,
                                  glm::vec2 size);

    void setMouseImage(const std::string& imageFile);

    void createFrameListener();

    void captureInput();

    // OIS::KeyListener
    bool keyPressed(const OIS::KeyEvent& arg) override;

    bool keyReleased(const OIS::KeyEvent& arg) override;

    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

    // OIS::MouseListener
    bool mousePressed(const OIS::MouseEvent& arg,
                      OIS::MouseButtonID id) override;

    bool mouseReleased(const OIS::MouseEvent& arg,
                       OIS::MouseButtonID id) override;

    bool mouseMoved(const OIS::MouseEvent& arg) override;

    void windowResized(Ogre::RenderWindow* rw);

    // Getters and setters
    CEGUI::OgreRenderer* getRenderer() const;
    CEGUI::GUIContext* getContext() const;
};