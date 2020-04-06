#ifdef _APP
#include "Game.h"
#include <fstream>
#include <iostream>
#endif
#ifdef _DEBUG
int main(int argc, char* args[])
#else
#include <windows.h>
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lmCmdLine,
                   int nCmdShow)
#endif
{
#ifdef _APP
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    try {
        Game game;
        if (game.init("Test"))
            game.run();
    } catch (std::exception& e) {
        std::cout << "\n"
                  << "================"
                  << "\n"
                  << "ERROR: " << e.what() << "\n"
                  << "================"
                  << "\n";
    }
#endif
    return 0;
}
