#pragma once

#include <string>
#include <CEGUI\CEGUI.h>
#include <CEGUI\RendererModules\OpenGL\GL3Renderer.h>
#include <glm\glm.hpp>
#include <CEGUI\RendererModules\Ogre\Renderer.h>

class GUI {
private:
	static CEGUI::OgreRenderer* m_renderer;
	CEGUI::GUIContext* m_context = nullptr;
	CEGUI::Window* m_root = nullptr;

public:
	void init(const std::string& _resourceDirectory);
	void destroy();
	void draw();

	void loadScheme(const std::string& schemeFile);
	void setFont(const std::string& fontFile);

	CEGUI::Window* createWidget(const std::string& type, glm::vec4 destRectPerc, glm::vec4 destRectPix, const std::string& name = "");
	static void setWidgetDestRect(CEGUI::Window* widget, glm::vec4 destRectPerc, glm::vec4 destRectPix);

	// Getters and setters
	static CEGUI::OgreRenderer* getRenderer();
	const CEGUI::GUIContext* getContext();

};

