#ifdef _DEBUG
int main(int argc, char* args[])
#else
#include <windows.h>
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lmCmdLine,
                   int nCmdShow)
#endif
{
    return 0;
}
