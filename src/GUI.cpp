#include "GUI.h"
#include "OIS.h"
#include "OgreLogManager.h"
#include "OgreRenderWindow.h"
#include "OgreRoot.h"
#include "OgreSDLContext.h"
#include <CEGUI\CEGUI.h>
#include <CEGUI\MouseCursor.h>
#include <CEGUI\RendererModules\Ogre\Renderer.h>
#include <CEGUI\RendererModules\Ogre\ResourceProvider.h>
#include <iostream>

void GUI::init(const std::string& _resourceDirectory) {
    if (m_renderer == nullptr) {

        m_renderer = &CEGUI::OgreRenderer::bootstrapSystem(
            *OgreSDLContext::getInstance()->getRenderTarget());

        CEGUI::OgreResourceProvider* rp =
            dynamic_cast<CEGUI::OgreResourceProvider*>(
                CEGUI::System::getSingleton().getResourceProvider());

        CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
        CEGUI::Font::setDefaultResourceGroup("Fonts");
        CEGUI::Scheme::setDefaultResourceGroup("Schemes");
        CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
        CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    }

    mWindow = OgreSDLContext::getInstance()->getRenderWindow();
    m_context = &CEGUI::System::getSingleton().createGUIContext(
        m_renderer->getDefaultRenderTarget());
    m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow",
                                                               "root");
    m_context->setRootWindow(m_root);

    createFrameListener();
}

void GUI::destroy() {
    CEGUI::System::getSingleton().destroyGUIContext(*m_context);
    m_renderer->destroySystem();
}

void GUI::draw() {
    m_renderer->beginRendering();
    m_context->draw();
    m_renderer->endRendering();
}

void GUI::loadScheme(const std::string& schemeFile) {
    CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void GUI::setFont(const std::string& fontFile) {
    CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
    m_context->setDefaultFont(fontFile);
}

CEGUI::PushButton* GUI::createPushButton(const std::string& text,
                                         glm::vec2 position, glm::vec2 size,
                                         const std::string& name) {
    CEGUI::PushButton* button = static_cast<CEGUI::PushButton*>(
        CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button",
                                                          name));
    setWidgetDestRect(button, position, size);

    button->setText(text);

    m_context->getRootWindow()->addChild(button);

    return button;
}

CEGUI::DefaultWindow* GUI::createFrameWindow(const std::string& text,
                                             glm::vec2 position, glm::vec2 size,
                                             const std::string& name) {
    CEGUI::DefaultWindow* statictext = static_cast<CEGUI::DefaultWindow*>(
        CEGUI::WindowManager::getSingleton().createWindow(
            "TaharezLook/StaticText", name));
    setWidgetDestRect(statictext, position, size);

    statictext->setText(text);
    statictext->setProperty("FrameEnabled", "false");
    statictext->setProperty("BackgroundEnabled", "false");

    m_context->getRootWindow()->addChild(statictext);

    return statictext;
}

void GUI::setWidgetDestRect(CEGUI::Window* widget, glm::vec2 position,
                            glm::vec2 size) {
    widget->setPosition(CEGUI::UVector2(CEGUI::UDim(position.x, 0),
                                        CEGUI::UDim(position.y, 0)));
    widget->setSize(
        CEGUI::USize(CEGUI::UDim(0, size.x), CEGUI::UDim(0, size.y)));
}

void GUI::setMouseImage(const std::string& imageFile) {
    CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .getMouseCursor()
        .setImage(imageFile);
}

void GUI::createFrameListener() {
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem(pl);

    mKeyboard = static_cast<OIS::Keyboard*>(
        mInputManager->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse*>(
        mInputManager->createInputObject(OIS::OISMouse, true));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    // Set initial mouse clipping size
    windowResized(mWindow);

    // TODO: Register as a Window listener
    // Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    OgreSDLContext::getInstance()->getOgreRoot()->addFrameListener(this);
}

bool GUI::frameRenderingQueued(/*const Ogre::FrameEvent& evt*/) {
    if (mWindow->isClosed())
        return false;

    // Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    // Need to inject timestamps to CEGUI System.
    // CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

    return true;
}

bool GUI::keyPressed(const OIS::KeyEvent& arg) {
    CEGUI::GUIContext& context =
        CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectKeyDown((CEGUI::Key::Scan)arg.key);
    context.injectChar((CEGUI::Key::Scan)arg.text);

    return true;
}

bool GUI::keyReleased(const OIS::KeyEvent& arg) {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
        (CEGUI::Key::Scan)arg.key);
    return true;
}

CEGUI::MouseButton GUI::convertButton(OIS::MouseButtonID buttonID) {
    switch (buttonID) {
    case OIS::MB_Left:
        return CEGUI::LeftButton;

    case OIS::MB_Right:
        return CEGUI::RightButton;

    case OIS::MB_Middle:
        return CEGUI::MiddleButton;

    default:
        return CEGUI::LeftButton;
    }
}

bool GUI::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {
    CEGUI::GUIContext& context =
        CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectMouseButtonDown(convertButton(id));
    std::cout << arg.state.X.abs << " " << arg.state.Y.abs << "\n";
    return true;
}

bool GUI::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(
        convertButton(id));
    return true;
}

bool GUI::mouseMoved(const OIS::MouseEvent& arg) {
    CEGUI::GUIContext& sys =
        CEGUI::System::getSingleton().getDefaultGUIContext();
    sys.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
    // Scroll wheel.
    if (arg.state.Z.rel)
        sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);
    return true;
}

void GUI::windowResized(Ogre::RenderWindow* rw) {
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState& ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

CEGUI::OgreRenderer* GUI::getRenderer() { return m_renderer; }

CEGUI::GUIContext* GUI::getContext() { return m_context; }
