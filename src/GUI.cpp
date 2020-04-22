#include "GUI.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "OIS.h"
#include "OgreSDLContext.h"
#include "Scene.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/MouseCursor.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <Ogre.h>
#include <iostream>
#include <json.h>

GuiComponent::GuiComponent() {
    mRenderer_ = &CEGUI::OgreRenderer::bootstrapSystem(
        *OgreSDLContext::getInstance()->getRenderTarget());
    mRoot_ = OgreSDLContext::getInstance()->getRoot();
    mWindow_ = OgreSDLContext::getInstance()->getRenderWindow();
    mContext_ = &CEGUI::System::getSingleton().getDefaultGUIContext();

    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

    mWindowManager_ = &CEGUI::WindowManager::getSingleton();
    sheet_ = mWindowManager_->createWindow("DefaultWindow", "CEGUIDemo/Sheet");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet_);

    createFrameListener();
}

GuiComponent::~GuiComponent() { destroy(); }

void GuiComponent::destroy() {
    // TODO: Remove memory leaks from loadScheme() and widgets

    mInputManager_->destroyInputObject(mMouse_);
    mInputManager_->destroyInputObject(mKeyboard_);
    OIS::InputManager::destroyInputSystem(mInputManager_);
    CEGUI::OgreRenderer::destroySystem();
}

void GuiComponent::createFrameListener() {
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow_->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager_ = OIS::InputManager::createInputSystem(pl);

    mKeyboard_ = reinterpret_cast<OIS::Keyboard*>(
        mInputManager_->createInputObject(OIS::OISKeyboard, true));
    mMouse_ = reinterpret_cast<OIS::Mouse*>(
        mInputManager_->createInputObject(OIS::OISMouse, true));

    mMouse_->setEventCallback(this);
    mKeyboard_->setEventCallback(this);

    // Set initial mouse clipping size
    windowResized(mWindow_);

    mRoot_->addFrameListener(this);
}

void GuiComponent::checkEvent() {
    mMouse_->capture();
//    mKeyboard_->capture();
}

void GuiComponent::windowResized(Ogre::RenderWindow* rw) {
    unsigned int width = 0, height = 0, depth = 0;
    int left = 0, top = 0;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState& ms = mMouse_->getMouseState();
    ms.width = static_cast<int>(width);
    ms.height = static_cast<int>(height);
}

// -------------- CEGUI RESOURCES --------------

void GuiComponent::loadScheme(const std::string& schemeFile) {
    CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void GuiComponent::setFont(const std::string& fontFile) {
    CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
    mContext_->setDefaultFont(fontFile);
}

void GuiComponent::setMouseImage(const std::string& imageFile) {
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
CEGUI::Window* GuiComponent::createButton(const std::string& text,
                                          const glm::vec2 position,
                                          const glm::vec2 size,
                                          const std::string& name) {
    CEGUI::Window* button = CEGUI::WindowManager::getSingleton().createWindow(
        "TaharezLook/Button", name);

    setWidgetDestRect(button, position, size);
    button->setText(text);
    sheet_->addChild(button);

    return button;
}

CEGUI::Window* GuiComponent::createLabel(const std::string& text,
                                         const glm::vec2 position,
                                         const glm::vec2 size,
                                         const std::string& name) {
    CEGUI::Window* label = CEGUI::WindowManager::getSingleton().createWindow(
        "TaharezLook/StaticText", name);
    setWidgetDestRect(label, position, size);

    label->setText(text);
    label->setProperty("FrameEnabled", "false");
    label->setProperty("BackgroundEnabled", "false");

    sheet_->addChild(label);

    return label;
}

void GuiComponent::setWidgetDestRect(CEGUI::Window* widget,
                                     const glm::vec2 position,
                                     const glm::vec2 size) {
    widget->setPosition(CEGUI::UVector2(CEGUI::UDim(position.x, 0),
                                        CEGUI::UDim(position.y, 0)));
    widget->setSize(
        CEGUI::USize(CEGUI::UDim(0, size.x), CEGUI::UDim(0, size.y)));
}

// ------------- INPUT -------------

bool GuiComponent::keyPressed(const OIS::KeyEvent& arg) {
    mContext_->injectKeyDown(static_cast<CEGUI::Key::Scan>(arg.key));
    mContext_->injectChar(static_cast<CEGUI::Key::Scan>(arg.text));

    return true;
}

bool GuiComponent::keyReleased(const OIS::KeyEvent& arg) {
    mContext_->injectKeyUp(static_cast<CEGUI::Key::Scan>(arg.key));
    return true;
}

CEGUI::MouseButton
GuiComponent::convertButton(const OIS::MouseButtonID buttonID) {
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

bool GuiComponent::mousePressed(const OIS::MouseEvent&,
                                const OIS::MouseButtonID id) {
    mContext_->injectMouseButtonDown(convertButton(id));
    return true;
}

bool GuiComponent::mouseReleased(const OIS::MouseEvent&,
                                 const OIS::MouseButtonID id) {
    mContext_->injectMouseButtonUp(convertButton(id));
    return true;
}

bool GuiComponent::mouseMoved(const OIS::MouseEvent& arg) {
    mContext_->injectMouseMove(static_cast<float>(arg.state.X.rel),
                               static_cast<float>(arg.state.Y.rel));
    // Scroll wheel.
    if (arg.state.Z.rel)
        mContext_->injectMouseWheelChange(static_cast<float>(arg.state.Z.rel) /
                                          120.0f);
    return true;
}

// ------------- GETTERS AND SETTERS --------------

CEGUI::OgreRenderer* GuiComponent::getRenderer() const { return mRenderer_; }

CEGUI::GUIContext* GuiComponent::getContext() const { return mContext_; }

// FACTORY INFRASTRUCTURE DEFINITION

GuiComponentFactory::GuiComponentFactory() = default;

Component* GuiComponentFactory::create(Entity* _father, Json::Value& _data,
                                       Scene* _scene) {
    GuiComponent* guiComponent = new GuiComponent();
    _scene->getComponentsManager()->addEC(guiComponent);

    guiComponent->setFather(_father);
    guiComponent->setScene(_scene);

    if (!_data["scheme"].isString())
        throw std::exception("GuiComponent: scheme is not a string");
    guiComponent->loadScheme(_data["scheme"].asString());

    if (!_data["mouseImage"].isString())
        throw std::exception("GuiComponent: mouseImage is not a string");
    guiComponent->setMouseImage(_data["mouseImage"].asString());

    if (!_data["font"].isString())
        throw std::exception("GuiComponent: font is not a string");
    guiComponent->setFont(_data["font"].asString());

    return guiComponent;
}

DEFINE_FACTORY(GuiComponent);