#include "OgreContext.h"
#include "Game.h"

#ifdef _DEBUG
int main()
#else
#include <windows.h>
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lmCmdLine, int nCmdShow)
#endif
{
    Game game;
    game.init("Menu");

    return 0;
}


