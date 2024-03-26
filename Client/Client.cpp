#include "pch.h"
#include "Engine.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    Engine engine;

    if (!engine.InitWin(hInstance, nCmdShow))
        return -1;

    return engine.Run();
}
