#include "OgreSDLContext.h"

#ifdef _DEBUG
int main(int argc, char* args[])
#else
#include <windows.h>
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lmCmdLine, int nCmdShow)
#endif
{
    OgreSDLContext app;
    app.initApp("Test");
    app.renderLoop();

    return 0;
}


