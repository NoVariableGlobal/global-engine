#include "TransformComponent.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "Scene.h"

#include <Ogre.h>
#include <json.h>

TransformComponent::TransformComponent() {
    position_ = new Ogre::Vector3();
    scale_ = new Ogre::Vector3();
    orientation_ = new Ogre::Vector3();
    originalOrientation_ = new Ogre::Vector3();
}

TransformComponent::~TransformComponent() {
    delete position_;
    delete scale_;
    delete orientation_;
    delete originalOrientation_;
}

void TransformComponent::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

Ogre::Vector3 TransformComponent::getPosition() const { return *position_; }
void TransformComponent::setPosition(const Ogre::Vector3 p) { *position_ = p; }

Ogre::Vector3 TransformComponent::getOrientation() const {
    return *orientation_;
}
void TransformComponent::setOrientation(const Ogre::Vector3 r) {
    *orientation_ = r;
}

Ogre::Vector3 TransformComponent::getScale() const { return *scale_; }
void TransformComponent::setScale(const Ogre::Vector3 s) { *scale_ = s; }

Ogre::Vector3 TransformComponent::getOriginalOrientation() const {
    return *originalOrientation_;
}

void TransformComponent::setOriginalOrientation(const Ogre::Vector3 r) {
    *originalOrientation_ = r;
}

// FACTORY INFRASTRUCTURE DEFINITION

TransformComponentFactory::TransformComponentFactory() = default;

Component* TransformComponentFactory::create(Entity* _father,
                                             Json::Value& _data,
                                             Scene* _scene) {
    TransformComponent* transformComponent = new TransformComponent();
    _scene->getComponentsManager()->addDC(transformComponent);

    transformComponent->setFather(_father);
    transformComponent->setScene(_scene);

    if (!_data["position"].isArray())
        throw std::exception("TransformComponent: position is not an array");
    transformComponent->setPosition(Ogre::Vector3(
        _data["position"][0].asFloat(), _data["position"][1].asFloat(),
        _data["position"][2].asFloat()));

    if (!_data["orientation"].isArray())
        throw std::exception("TransformComponent: orientation is not an array");
    transformComponent->setOriginalOrientation(Ogre::Vector3(
        _data["orientation"][0].asFloat(), _data["orientation"][1].asFloat(),
        _data["orientation"][2].asFloat()));
    transformComponent->setOrientation(
        transformComponent->getOriginalOrientation());

    if (!_data["scale"].isArray())
        throw std::exception("TransformComponent: scale is not an array");
    transformComponent->setScale(Ogre::Vector3(_data["scale"][0].asFloat(),
                                               _data["scale"][1].asFloat(),
                                               _data["scale"][2].asFloat()));

    return transformComponent;
}

DEFINE_FACTORY(TransformComponent);