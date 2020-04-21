#include "DebugDrawer.h"

inline btVector3 cvt(const Ogre::Vector3& V) {
    return btVector3(V.x, V.y, V.z);
}

inline Ogre::Vector3 cvt(const btVector3& V) {
    return Ogre::Vector3(V.x(), V.y(), V.z());
}

inline btQuaternion cvt(const Ogre::Quaternion& Q) {
    return {Q.x, Q.y, Q.z, Q.w};
};

inline Ogre::Quaternion cvt(const btQuaternion& Q) {
    return Ogre::Quaternion(Q.w(), Q.x(), Q.y(), Q.z());
};

using namespace Ogre;

OgreDebugDrawer::OgreDebugDrawer(SceneManager* scm) {
    mContactPoints_ = &mContactPoints1_;
    mLines_ = new ManualObject("physics lines");
    // ASSERT(mLines);
    mTriangles_ = new ManualObject("physics triangles");
    // ASSERT(mTriangles);
    mLines_->setDynamic(true);
    mTriangles_->setDynamic(true);
    // mLines->estimateVertexCount( 100000 );
    // mLines->estimateIndexCount( 0 );

    scm->getRootSceneNode()->attachObject(mLines_);
    scm->getRootSceneNode()->attachObject(mTriangles_);

    static auto matName = "OgreBulletCollisionsDebugDefault";
    MaterialPtr mtl =
        MaterialManager::getSingleton().getDefaultSettings()->clone(matName);
    mtl->setReceiveShadows(false);
    mtl->setSceneBlending(SBT_TRANSPARENT_ALPHA);
    mtl->setDepthBias(0.1f, 0.0f);
    TextureUnitState* tu =
        mtl->getTechnique(0)->getPass(0)->createTextureUnitState();
    // ASSERT(tu);
    tu->setColourOperationEx(LBX_SOURCE1, LBS_DIFFUSE);
    mtl->getTechnique(0)->setLightingEnabled(false);
    // mtl->getTechnique(0)->setSelfIllumination( ColourValue::White );

    mLines_->begin(matName, RenderOperation::OT_LINE_LIST);
    mLines_->position(Vector3::ZERO);
    mLines_->colour(ColourValue::Blue);
    mLines_->position(Vector3::ZERO);
    mLines_->colour(ColourValue::Blue);

    mTriangles_->begin(matName, RenderOperation::OT_TRIANGLE_LIST);
    mTriangles_->position(Vector3::ZERO);
    mTriangles_->colour(ColourValue::Blue);
    mTriangles_->position(Vector3::ZERO);
    mTriangles_->colour(ColourValue::Blue);
    mTriangles_->position(Vector3::ZERO);
    mTriangles_->colour(ColourValue::Blue);

    mDebugModes_ = DBG_DrawWireframe;
    Root::getSingleton().addFrameListener(this);
}

OgreDebugDrawer::~OgreDebugDrawer() {
    Root::getSingleton().removeFrameListener(this);
    delete mLines_;
    delete mTriangles_;
}

void OgreDebugDrawer::drawLine(const btVector3& from, const btVector3& to,
                               const btVector3& color) {
    ColourValue c(color.getX(), color.getY(), color.getZ());
    c.saturate();
    mLines_->position(cvt(from));
    mLines_->colour(c);
    mLines_->position(cvt(to));
    mLines_->colour(c);
}

void OgreDebugDrawer::drawTriangle(const btVector3& v0, const btVector3& v1,
                                   const btVector3& v2, const btVector3& color,
                                   const btScalar alpha) {
    ColourValue c(color.getX(), color.getY(), color.getZ(), alpha);
    c.saturate();
    mTriangles_->position(cvt(v0));
    mTriangles_->colour(c);
    mTriangles_->position(cvt(v1));
    mTriangles_->colour(c);
    mTriangles_->position(cvt(v2));
    mTriangles_->colour(c);
}

void OgreDebugDrawer::drawContactPoint(const btVector3& PointOnB,
                                       const btVector3& normalOnB,
                                       const btScalar distance,
                                       const int lifeTime,
                                       const btVector3& color) {
    mContactPoints_->resize(mContactPoints_->size() + 1);
    auto& p = *(mContactPoints_->end() - 1);
    p.from = cvt(PointOnB);
    p.to = p.from + cvt(normalOnB) * distance;
    p.dieTime = Root::getSingleton().getTimer()->getMilliseconds() + lifeTime;
    p.color.r = color.x();
    p.color.g = color.y();
    p.color.b = color.z();
}

bool OgreDebugDrawer::frameStarted(const FrameEvent& /*evt*/) {
    const size_t now = Root::getSingleton().getTimer()->getMilliseconds();
    std::vector<ContactPoint>* newCP = mContactPoints_ == &mContactPoints1_
                                           ? &mContactPoints2_
                                           : &mContactPoints1_;
    for (auto i = mContactPoints_->begin(); i < mContactPoints_->end(); ++i) {
        ContactPoint& cp = *i;
        mLines_->position(cp.from);
        mLines_->colour(cp.color);
        mLines_->position(cp.to);
        if (now <= cp.dieTime)
            newCP->push_back(cp);
    }
    mContactPoints_->clear();
    mContactPoints_ = newCP;

    mLines_->end();
    mTriangles_->end();

    return true;
}

bool OgreDebugDrawer::frameEnded(const FrameEvent& evt) {
    mLines_->beginUpdate(0);
    mTriangles_->beginUpdate(0);
    return true;
}

void OgreDebugDrawer::reportErrorWarning(const char* warningString) {
    LogManager::getSingleton().getDefaultLog()->logMessage(warningString);
}

void OgreDebugDrawer::draw3dText(const btVector3& location,
                                 const char* textString) {}

void OgreDebugDrawer::setDebugMode(int debugMode) {
    mDebugModes_ = static_cast<DebugDrawModes>(debugMode);
}

int OgreDebugDrawer::getDebugMode() const { return mDebugModes_; }