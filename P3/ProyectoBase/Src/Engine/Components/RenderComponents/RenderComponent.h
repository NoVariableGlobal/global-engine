#pragma
#include "../Component.h"

namespace Ogre {
	class SceneManager;
}

class RenderComponent : public Component {
	protected:
		Ogre::SceneManager* mSM;

	public:
		RenderComponent();
		virtual ~RenderComponent();

		virtual void render() = 0;
};
