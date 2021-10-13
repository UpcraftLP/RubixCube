//
// Created by Joshua Schirra on 10/5/2021.
//

#pragma once

#include "../definitions.h"
#include "../render/window.h"
#include "../render/menu/screen.h"
#include "../render/menu/mainMenu.h"
#include <memory>

namespace Rubix {

    class Application {
    private:
        static Application *INSTANCE;
    public:
        static Application *getInstance() {
            return INSTANCE;
        }

        std::unique_ptr<Render::Window> window;
        Menu::Screen *currentScreen = nullptr;

        Application(const Application &application) = delete;

        Application(Application &&application) = delete;

        Application() {
            INSTANCE = this;
            r_debug("Hello, World!")
            int openGlVersion[3];
            glfwGetVersion(openGlVersion, openGlVersion + 1, openGlVersion + 2);
            std::cout << "OpenGL backend version " << openGlVersion[0] << "." << openGlVersion[1] << "." << openGlVersion[2] << "\n";
            window = Render::Window::create("RubixCube");
            glClearColor(0.2F, 0.2F, 0.2F, 1.0F);
        }

        ~Application() {
            INSTANCE = nullptr;
        }

        void run() {
            // TODO start main application thread
            Menu::MainMenu titleScreen;
            currentScreen = &titleScreen;

            double lastTime = glfwGetTime();
            while (window->alive()) {
                double currentTime = glfwGetTime();
                double delta = currentTime - lastTime;
                window->beginFrame();
                render(delta);
                window->endFrame();
                lastTime = currentTime;
            }
        }

        void render(double delta) {
            int fbWidth = window->getWidth();
            int fbHeight = window->getHeight();

            // TODO render world

            if(currentScreen != nullptr) {
                currentScreen->render((int) (fbWidth * getScreenScale()), (int) (fbHeight * getScreenScale()), 0, 0, delta);
            }
        }

        double getScreenScale() {
            return 1.0; // TODO ui scale
        }
    };
}
