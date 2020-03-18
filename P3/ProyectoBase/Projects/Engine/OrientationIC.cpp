#include "OrientationIC.h"
#include "Factory.h"
#include "FactoriesFactory.h"
#include "ComponentsManager.h"
#include "Scene.h"

#include "OgreRoot.h"

#include <json.h>

#include <iostream>

void OrientationIC::handleInput(const SDL_Event& _event)
{
	// Obtain the relative position of the mouse relative to the position of the character in screen
}

void OrientationIC::setOrientation(float orientation)
{
	_orientation = orientation;
}

// FACTORY INFRASTRUCTURE
class OrientationICFactory : public ComponentFactory {
public:
	OrientationICFactory() = default;
	virtual Component* create(Entity* _father, Json::Value& _data, Scene* scene)
	{
		// Create the component
		auto entityOrientation = new OrientationIC();
		scene->getComponentsManager()->addIC(entityOrientation);

		// Set the component's father as the entity it was instanced for
		entityOrientation->setFather(_father);

		// Read the orientation data
		/// IDL-Entity: { float orientation }
		const auto orientation = _data["orientation"];
		if (orientation.isNull) throw std::exception("OrientationIC: speed is not an int");
		entityOrientation->setOrientation(orientation.asFloat());

		return entityOrientation;
	};
};

REGISTER_FACTORY("OrientationIC", OrientationIC);
