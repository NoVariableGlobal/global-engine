#include "GuiContext.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "OgreSDLContext.h"
#include "Scene.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/MouseCursor.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <Ogre.h>
#include <iostream>
#include <json.h>

GuiContext* GuiContext::instance_ = nullptr;

void GuiContext::init() { instance_ = new GuiContext(); }

GuiContext* GuiContext::getInstance() { return instance_; }

GuiContext::GuiContext() {
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

void GuiContext::destroy() {
    // TODO: Remove memory leaks from loadScheme() and widgets
    CEGUI::OgreRenderer::destroySystem();
    delete instance_;
}

void GuiContext::createFrameListener() {
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow_->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;

    // Set initial mouse clipping size
    windowResized(mWindow_);

    mRoot_->addFrameListener(this);
}

void GuiContext::captureInput(const SDL_Event& event) {

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT)
            mContext_->injectMouseButtonDown(CEGUI::LeftButton);
        else if (event.button.button == SDL_BUTTON_RIGHT)
            mContext_->injectMouseButtonDown(CEGUI::RightButton);

    } else if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT)
            mContext_->injectMouseButtonUp(CEGUI::LeftButton);
        else if (event.button.button == SDL_BUTTON_RIGHT)
            mContext_->injectMouseButtonUp(CEGUI::RightButton);

    } else if (event.type == SDL_MOUSEMOTION) {
        mContext_->injectMousePosition((event.motion.x), (event.motion.y));

    } else if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED ||
               event.window.event == SDL_WINDOWEVENT_RESIZED ||
               event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        windowResized(mWindow_);
}

void GuiContext::windowResized(Ogre::RenderWindow* rw) {
    unsigned int width = 0, height = 0, depth = 0;
    int left = 0, top = 0;
    rw->getMetrics(width, height, depth, left, top);
    CEGUI::Sizef newSize(width, height);

    // mRenderer_->setDisplaySize(newSize);
    CEGUI::System::getSingleton().notifyDisplaySizeChanged(newSize);
}

// -------------- CEGUI RESOURCES --------------

void GuiContext::loadScheme(const std::string& schemeName,
                            const std::string& schemeFile) {
    schemeName_ = schemeName;
    CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void GuiContext::setFont(const std::string& fontFile) {
    CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
    mContext_->setDefaultFont(fontFile);

    mContext_->getDefaultFont()->setAutoScaled(
        CEGUI::AutoScaledMode::ASM_Disabled);
}

void GuiContext::setMouseImage(const std::string& imageFile) {
    CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .getMouseCursor()
        .setDefaultImage(imageFile);

    CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .getMouseCursor()
        .setImage(imageFile);
}

void GuiContext::setMouseVisibility(bool b) {
    if (b)
        CEGUI::System::getSingleton()
            .getDefaultGUIContext()
            .getMouseCursor()
            .show();
    else
        CEGUI::System::getSingleton()
            .getDefaultGUIContext()
            .getMouseCursor()
            .hide();
}

// -------------- GUI ELEMENTS --------------
CEGUI::Window* GuiContext::createButton(const std::string& text,
                                        const glm::vec2 position,
                                        const glm::vec2 size,
                                        const std::string& name) {
    CEGUI::Window* button = CEGUI::WindowManager::getSingleton().createWindow(
        schemeName_ + "/Button", name);

    setWidgetDestRect(button, position, size);
    button->setText(text);
    sheet_->addChild(button);

    return button;
}

CEGUI::Window* GuiContext::createLabel(const std::string& text,
                                       const glm::vec2 position,
                                       const glm::vec2 size,
                                       const std::string& name) {
    CEGUI::Window* label = CEGUI::WindowManager::getSingleton().createWindow(
        schemeName_ + "/StaticText", name);
    setWidgetDestRect(label, position, size);

    label->setText(text);
    label->setProperty("FrameEnabled", "false");
    label->setProperty("BackgroundEnabled", "false");

    sheet_->addChild(label);

    return label;
}

CEGUI::Window* GuiContext::createImage(const std::string& image,
                                       glm::vec2 position, glm::vec2 size,
                                       const std::string& name) {
    CEGUI::Window* staticImage =
        CEGUI::WindowManager::getSingleton().createWindow(
            schemeName_ + "/StaticImage", name);
    setWidgetDestRect(staticImage, position, size);

    staticImage->setProperty("FrameEnabled", "false");
    staticImage->setProperty("BackgroundEnabled", "false");
    staticImage->setProperty("Image", image);

    sheet_->addChild(staticImage);

    return staticImage;
}

void GuiContext::setWidgetDestRect(CEGUI::Window* widget,
                                   const glm::vec2 position,
                                   const glm::vec2 size) {
    widget->setPosition(CEGUI::UVector2(CEGUI::UDim(position.x, 0),
                                        CEGUI::UDim(position.y, 0)));
    widget->setSize(
        CEGUI::USize(CEGUI::UDim(0, size.x), CEGUI::UDim(0, size.y)));
}

// ------------- GETTERS AND SETTERS --------------

CEGUI::OgreRenderer* GuiContext::getRenderer() const { return mRenderer_; }

CEGUI::GUIContext* GuiContext::getContext() const { return mContext_; }
