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

void GUI::init(std::string scheme) {
    mRenderer = &CEGUI::OgreRenderer::bootstrapSystem(
        *OgreSDLContext::getInstance()->getRenderTarget());
    mRoot = OgreSDLContext::getInstance()->getOgreRoot();
    mWindow = OgreSDLContext::getInstance()->getRenderWindow();
    mContext = &CEGUI::System::getSingleton().getDefaultGUIContext();

    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

    // TODO: Make this non scheme-dependant
    loadScheme(scheme);
    setMouseImage("TaharezLook/MouseArrow");
    setFont("DejaVuSans-14");

    mWindowManager = &CEGUI::WindowManager::getSingleton();
    sheet = mWindowManager->createWindow("DefaultWindow", "CEGUIDemo/Sheet");

    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
    createFrameListener();
}

void GUI::destroy() {
    // TODO: Remove memory leaks from loadScheme() and widgets

    mInputManager->destroyInputObject(mMouse);
    mInputManager->destroyInputObject(mKeyboard);
    OIS::InputManager::destroyInputSystem(mInputManager);

    mRenderer->destroySystem();
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

    mRoot->addFrameListener(this);
}

void GUI::captureInput() {
    mKeyboard->capture();
    mMouse->capture();
}

void GUI::windowResized(Ogre::RenderWindow* rw) {
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState& ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

void GUI::draw() {
    mRenderer->beginRendering();
    mContext->draw();
    mRenderer->endRendering();
}

// -------------- CEGUI RESOURCES --------------

void GUI::loadScheme(const std::string& schemeFile) {
    CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void GUI::setFont(const std::string& fontFile) {
    CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
    mContext->setDefaultFont(fontFile);
}

void GUI::setMouseImage(const std::string& imageFile) {
    CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .getMouseCursor()
        .setDefaultImage(imageFile);

    CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .getMouseCursor()
        .setImage(imageFile);
}

// -------------- GUI ELEMENTS --------------
CEGUI::Window* GUI::createButton(const std::string& text, glm::vec2 position,
                                 glm::vec2 size, const std::string& name) {
    CEGUI::Window* button = CEGUI::WindowManager::getSingleton().createWindow(
        "TaharezLook/Button", name);

    setWidgetDestRect(button, position, size);
    button->setText(text);
    sheet->addChild(button);

    return button;
}

CEGUI::Window* GUI::createLabel(const std::string& text, glm::vec2 position,
                                glm::vec2 size, const std::string& name) {
    CEGUI::Window* label = CEGUI::WindowManager::getSingleton().createWindow(
        "TaharezLook/StaticText", name);
    setWidgetDestRect(label, position, size);

    label->setText(text);
    label->setProperty("FrameEnabled", "false");
    label->setProperty("BackgroundEnabled", "false");

    sheet->addChild(label);

    return label;
}

void GUI::setWidgetDestRect(CEGUI::Window* widget, glm::vec2 position,
                            glm::vec2 size) {
    widget->setPosition(CEGUI::UVector2(CEGUI::UDim(position.x, 0),
                                        CEGUI::UDim(position.y, 0)));
    widget->setSize(
        CEGUI::USize(CEGUI::UDim(0, size.x), CEGUI::UDim(0, size.y)));
}

// ------------- INPUT -------------

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

// ------------- GETTERS AND SETTERS --------------

CEGUI::OgreRenderer* GUI::getRenderer() { return mRenderer; }

CEGUI::GUIContext* GUI::getContext() { return mContext; }
