//
// Created by Joshua Schirra on 10/5/2021.
//

#pragma once

#include "../definitions.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include "backgroundWindow.h"
#include <memory>

using namespace Rubix;

namespace Rubix::Util {
    void _framebufferCallback(GLFWwindow *windowHandle, int width, int height);
}

namespace Rubix::Render {

    class Window {
    private:
        GLFWwindow *hWND;
        int framebufferWidth = 0;
        int framebufferHeight = 0;
        bool resized = false;

    public:
        static std::unique_ptr<Window> create(std::string &&title) {
            if (!glfwInit()) {
                r_exception("Unable to initialize GLFW")
            }

            auto *monitor = glfwGetPrimaryMonitor();
            auto *videoMode = glfwGetVideoMode(monitor);

#if RUBIX_BG_WINDOW
            return std::make_unique<Window>(std::forward<std::string>(title), videoMode->width, videoMode->height, std::forward<GLFWmonitor *>(nullptr));
#else
            return std::make_unique<Window>(std::forward<std::string>(title), videoMode->width, videoMode->height + 1, std::forward<GLFWmonitor *>(nullptr));
#endif

        }

        Window(std::string &&title, int width, int height, GLFWmonitor *monitor) {
            glfwDefaultWindowHints();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if RUBIX_DEBUG
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

            // TODO undecorated window in all cases
#if RUBIX_BG_WINDOW
            glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
            glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
#endif

            hWND = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
            if (!hWND) {
                r_exception("Failed to create Window")
            }
            glfwMakeContextCurrent(hWND);
            glewExperimental = GL_TRUE;
            auto err = glewInit();
            if (err != GLEW_OK) {
                r_exception(reinterpret_cast<const char *>(glewGetErrorString(err)))
            }
#if RUBIX_VSYNC
            glfwSwapInterval(1); // vsync
#endif
            glfwSetFramebufferSizeCallback(hWND, Util::_framebufferCallback);
            glfwGetFramebufferSize(hWND, &framebufferWidth, &framebufferHeight);
            onResize(framebufferWidth, framebufferHeight);
        }

        ~Window() {
            glfwDestroyWindow(hWND);
            glfwTerminate();
        }

        void onResize(int fbWidth, int fbHeight) {
            framebufferWidth = fbWidth;
            framebufferHeight = fbHeight;
            resized = true;
            glViewport(0, 0, fbWidth, fbHeight);
        }

        bool alive() {
            return !glfwWindowShouldClose(hWND);
        }

        void beginFrame() {
            if(resized) {
                // TODO handle anything that needs to be resized
                resized = false;
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void endFrame() {
            glfwSwapBuffers(hWND);
            glfwPollEvents();
        }

        GLFWwindow *handle() {
            return hWND;
        }

        int getWidth() {
            return framebufferWidth;
        }

        int getHeight() {
            return framebufferHeight;
        }
    };
}