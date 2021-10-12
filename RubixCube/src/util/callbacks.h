//
// Created by Joshua Schirra on 10/5/2021.
//

#pragma once

#include "../definitions.h"
#include "../main/application.h"

namespace Rubix::Util {

    void error_callback(int error, const char *description) {
        std::cerr << "OPENGL ERROR: " << error << " " << description << "\n";
        fprintf(stderr, "OPENGL ERROR %d: %s\n", error, description);
    }

    void framebufferCallback(GLFWwindow *windowHandle, int width, int height) {
        auto app = Application::getInstance();
        auto window = *app->window;
        if (window.handle() == windowHandle) {
            window.onResize(width, height);
            if (app->currentScreen != nullptr) {
                app->currentScreen->init(width, height);
            }
        }

    }
}