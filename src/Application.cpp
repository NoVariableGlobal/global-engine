#include <OgreRoot.h>

#undef main

int main()
{
    Ogre::Root* root;

#ifdef _DEBUG
    root = new Ogre::Root("plugins_d.cfg");
#else
    root = new Ogre::Root("plugins.cfg");
#endif

    return 0;
}
