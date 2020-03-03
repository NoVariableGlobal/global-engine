#include "ApplicationContext.h"

#ifdef _DEBUG
int main()
#else
#include <windows.h>
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lmCmdLine, int nCmdShow)
#endif
{
    ApplicationContext app;
    app.initApp("Test");
    app.renderLoop();

    return 0;
}


