#include "GUI.h"
#include "OgreSDLContext.h"
#include <iostream>

CEGUI::OgreRenderer* GUI::m_renderer = nullptr;

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

    m_context = &CEGUI::System::getSingleton().createGUIContext(
        m_renderer->getDefaultRenderTarget());
    m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow",
                                                               "root");
    m_context->setRootWindow(m_root);
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

CEGUI::Window* GUI::createWidget(const std::string& type,
                                 glm::vec4 destRectPerc, glm::vec4 destRectPix,
                                 const std::string& name) {
    CEGUI::Window* newWindow =
        CEGUI::WindowManager::getSingleton().createWindow(type, name);
    m_root->addChild(newWindow);
    setWidgetDestRect(newWindow, destRectPerc, destRectPix);
    return newWindow;
}

void GUI::setWidgetDestRect(CEGUI::Window* widget, glm::vec4 destRectPerc,
                            glm::vec4 destRectPix) {
    widget->setPosition(
        CEGUI::UVector2(CEGUI::UDim(destRectPerc.x, destRectPix.x),
                        CEGUI::UDim(destRectPerc.y, destRectPix.y)));
    widget->setSize(CEGUI::USize(CEGUI::UDim(destRectPerc.z, destRectPix.z),
                                 CEGUI::UDim(destRectPerc.w, destRectPix.w)));
}

void GUI::setMouseImage(const std::string& imageFile) {
    CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .getMouseCursor()
        .setDefaultImage(imageFile);
}

CEGUI::OgreRenderer* GUI::getRenderer() { return m_renderer; }

const CEGUI::GUIContext* GUI::getContext() { return m_context; }
