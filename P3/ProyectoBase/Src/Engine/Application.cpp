#include "Game.h"
#include "checkML.h"
#include "OgreSDLContext.h"

#ifdef _DEBUG
int main(int argc, char* args[])
#else
#include <windows.h>
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lmCmdLine, int nCmdShow)
#endif
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	Game game;
	game.init("Game");
	game.update();

	return 0;
}
