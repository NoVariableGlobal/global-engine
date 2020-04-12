#pragma once

#include "OISKeyboard.h"
#include "OISMouse.h"
#include "OgreFrameListener.h"
#include "CEGUI\InputEvent.h"
#include <glm\glm.hpp>
#include <string>

namespace CEGUI {
    class OgreRenderer;
    class GUIContext;
    class Window;
} // namespace CEGUI

namespace OIS {
    class InputManager;
    class Keyboard;
    class Mouse;
} // namespace OIS

class GUI : public OIS::KeyListener,
            public OIS::MouseListener,
            public Ogre::FrameListener {
  private:
    Ogre::RenderWindow* mWindow;

    CEGUI::OgreRenderer* m_renderer = nullptr;
    CEGUI::GUIContext* m_context = nullptr;
    CEGUI::Window* m_root = nullptr;

    OIS::InputManager* mInputManager;
    OIS::Mouse* mMouse;
    OIS::Keyboard* mKeyboard;

  public:
    void init(const std::string& _resourceDirectory);
    void destroy();
    void draw();

    void loadScheme(const std::string& schemeFile);

    void setFont(const std::string& fontFile);

    CEGUI::Window* createWidget(const std::string& type, glm::vec4 destRectPerc,
                                glm::vec4 destRectPix,
                                const std::string& name = "");

    static void setWidgetDestRect(CEGUI::Window* widget, glm::vec4 destRectPerc,
                                  glm::vec4 destRectPix);

    void setMouseImage(const std::string& imageFile);

    void createFrameListener();

    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    bool keyPressed(const OIS::KeyEvent& arg);

    bool keyReleased(const OIS::KeyEvent& arg);

    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

    bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

    bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

    bool mouseMoved(const OIS::MouseEvent& arg);

    void windowResized(Ogre::RenderWindow* rw);

    // Getters and setters
    CEGUI::OgreRenderer* getRenderer();
    CEGUI::GUIContext* getContext();
};