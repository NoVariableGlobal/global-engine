#include "ApplicationContext.h"
#include <exception>
#include <iostream>

#ifdef _DEBUG
int main()
#else
#include <windows.h>
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lmCmdLine, int nCmdShow)
#endif
{
    try {
        ApplicationContext app;
        app.initApp("Test");
        app.renderLoop();
    } catch (const std::exception& exception) {
        std::cerr << "FATAL ERROR: " << exception.what() << "\n";
    }

    return 0;
}


