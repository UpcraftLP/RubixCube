#include "definitions.h"
#include "util/callbacks.h"
#include "main/application.h"
#include "render/backgroundWindow.h"
#include "util/threads.h"
#include <Windows.h>

using namespace Rubix;

Application *Application::INSTANCE = nullptr;

#ifndef NDEBUG
int main() {
#else
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) { // need WinMain() to not get a pesky console window
#endif

    Util::setThreadName(L"Render Thread");

    auto mutex = CreateMutex(nullptr, FALSE, "RubixCube Game");
    if (!mutex) {
        r_exception("CreateMutex error: " + std::to_string(GetLastError()))
    }

    // https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject
    switch (WaitForSingleObject(mutex, 10L)) {
        case WAIT_ABANDONED:
        case WAIT_OBJECT_0:
            break;
        default:
            // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
            MessageBox(nullptr, "Another instance of the game is already running!", "Error", MB_OK);
            return EXIT_FAILURE;
    }

#if RUBIX_NOSTART
    r_debug("NOSTART flag found, shutting down.")
    return 0;
#endif

    glfwSetErrorCallback(Util::_errorCallback);
    Application main;
#if RUBIX_BG_WINDOW
    BackgroundWnd::setBackgroundWindow(main.window->handle());
#endif
    main.run();

    return EXIT_SUCCESS;
}

