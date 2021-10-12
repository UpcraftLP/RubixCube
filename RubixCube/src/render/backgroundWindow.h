//
// Created by Joshua Schirra on 10/5/2021.
//

#pragma once

#include "../definitions.h"
#include <windows.h>

#define GLFW_EXPOSE_NATIVE_WIN32 // https://www.glfw.org/docs/3.3/group__native.html

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace Rubix::BackgroundWnd {

    static constexpr uint32_t WM_SPAWN_WORKER = 0x052C;

    static BOOL CALLBACK findWorker(HWND wnd, LPARAM lp);

    void setBackgroundWindow(GLFWwindow *glfwWindow) {
        auto hWND = glfwGetWin32Window(glfwWindow);

        auto progMan = FindWindowA("Progman", nullptr);

        // magic: send an undocumented window message to Progman to spawn a Worker window behind desktop icons
        // https://www.codeproject.com/Articles/856020/Draw-Behind-Desktop-Icons-in-Windows-plus?msg=5478543#xx5478543xx
        //
        // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendmessage
        SendMessage(progMan, WM_SPAWN_WORKER, 0x0000000D, 0);
        SendMessage(progMan, WM_SPAWN_WORKER, 0x0000000D, 1);

        HWND worker;
        EnumWindows(findWorker, reinterpret_cast<LPARAM>(&worker));
        SetParent(hWND, worker);
    }

    BOOL findWorker(HWND wnd, LPARAM lp) {
        if (!FindWindowExA(wnd, nullptr, "SHELLDLL_DefView", nullptr)) {
            return TRUE;
        }

        auto workerW = FindWindowExA(nullptr, wnd, "WorkerW", nullptr);
        *reinterpret_cast<HWND *>(lp) = workerW;
        if (workerW) {
            return FALSE;
        }

        return TRUE;
    }

}