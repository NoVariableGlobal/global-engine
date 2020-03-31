#include "Game.h"

#include <iostream>

#ifdef _DEBUG
int main(int argc, char* args[])
#else
#include <windows.h>
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lmCmdLine,
                   int nCmdShow)
#endif
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    try {
        Game game;
        if (game.init("MOOD"))
            game.run();
    } catch (std::exception& e) {
        std::cout << "\n" << "================" << "\n" << "ERROR: " << e.what()
                  << "\n" << "================" << "\n";
    }

    return 0;
}
