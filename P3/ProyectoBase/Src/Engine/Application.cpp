#include <OgreRoot.h> // como no lo tenemos metido en nuestro proyecto es mejor poner <> que ""


#ifdef _DEBUG
int main()
#else
#include <windows.h>
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lmCmdLine, int nCmdShow)
#endif
{
    Ogre::Root* root;

#ifdef _DEBUG
    root = new Ogre::Root("plugins_d.cfg");
#else
    root = new Ogre::Root("plugins.cfg");
#endif

    return 0;
}


