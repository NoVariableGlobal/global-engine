#include "ApplicationContext.h"
#include "Game.h"

#include <OgreRoot.h> // como no lo tenemos metido en nuestro proyecto es mejor poner <> que ""

#ifdef _DEBUG
int main()
#else
#include <windows.h>
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lmCmdLine, int nCmdShow)
#endif
{
    Game game;
    game.init("Game");
    ApplicationContext app;
    app.initApp("Test");
    app.renderLoop();

    return 0;
}


