#pragma once

#include "CEGUI\InputEvent.h"
#include "OISKeyboard.h"
#include "OISMouse.h"
#include "OgreFrameListener.h"
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
            //public Ogre::WindowEventListener,
            public Ogre::FrameListener {
  private:
    Ogre::RenderWindow* mWindow;
    CEGUI::OgreRenderer* mRenderer = nullptr;
    Ogre::Root* mRoot = nullptr;
    CEGUI::GUIContext* mContext = nullptr;

	CEGUI::Window* sheet;
    CEGUI::WindowManager* mWindowManager;

    OIS::InputManager* mInputManager;
    OIS::Mouse* mMouse;
    OIS::Keyboard* mKeyboard;

  public:
    void init(std::string scheme);
    void destroy();
    void draw();

    void loadScheme(const std::string& schemeFile);

    void setFont(const std::string& fontFile);

    CEGUI::Window* createButton(const std::string& text, glm::vec2 position,
                                glm::vec2 size, const std::string& name);

    CEGUI::Window* createLabel(const std::string& text,
                                            glm::vec2 position, glm::vec2 size,
                                            const std::string& name = "");

    static void setWidgetDestRect(CEGUI::Window* widget, glm::vec2 position,
                                  glm::vec2 size);

    void setMouseImage(const std::string& imageFile);

    void createFrameListener();

    bool frameRenderingQueued(/*const Ogre::FrameEvent& evt*/);

    // OIS::KeyListener
    bool keyPressed(const OIS::KeyEvent& arg);

    bool keyReleased(const OIS::KeyEvent& arg);

    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

    // OIS::MouseListener
    bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

    bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

    bool mouseMoved(const OIS::MouseEvent& arg);

    void windowResized(Ogre::RenderWindow* rw);

    // Getters and setters
    CEGUI::OgreRenderer* getRenderer();
    CEGUI::GUIContext* getContext();
};