#pragma
#include "Component.h"

// Abstract subcomponent from which every graphic component should inherit

namespace Ogre
{
	typedef class Entity;
	typedef class SceneNode;
}

class RenderComponent : public Component {
protected:
	Ogre::Entity* entity = nullptr;
	Ogre::SceneNode* sceneNode = nullptr;

public:
	RenderComponent();
	virtual ~RenderComponent();
	virtual void render() = 0;

	// Getters and setters
	Ogre::Entity* getOgreEntity();
	void setOgreEntity(Ogre::Entity* e);

	Ogre::SceneNode* getSceneNode();
	void setSceneNode(Ogre::SceneNode* sn);
};
