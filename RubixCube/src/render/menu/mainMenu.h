//
// Created by Joshua Schirra on 10/5/2021.
//

#pragma once

#include "../../definitions.h"
#include "screen.h"

using namespace Rubix;

namespace Rubix::Menu {

    class MainMenu : public Screen {

    public:
        void render(int screenWidth, int screenHeight, int mouseX, int mouseY, double delta) override {
            glClearColor(abs(sinf((float)glfwGetTime() / 8.0F + 2.0F)), abs(sinf((float)glfwGetTime() / 6.0F + 1.3F)), abs(sinf((float)glfwGetTime() / 10.0F)), 1.0F);
        }
        void init(int screenWidth, int screenHeight) override {

        }
    };
}