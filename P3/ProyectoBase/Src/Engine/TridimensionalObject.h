#pragma once

#include <string>
#include "RenderComponent.h"

namespace Ogre
{
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<3, Real> Vector3;
	typedef class Entity;
	typedef class SceneNode;
}

class TridimensionalObject : public RenderComponent {
private:
	Ogre::Entity* _entity;
	Ogre::SceneNode* _sceneNode;

public:
	TridimensionalObject();
	~TridimensionalObject();

	void render();
	void setMaterial(std::string material);

	// Getters and setters
	Ogre::Entity* getOgreEntity();
	void setOgreEntity(Ogre::Entity* e);

	Ogre::SceneNode* getSceneNode();
	void setSceneNode(Ogre::SceneNode* sn);
};

