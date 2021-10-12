//
// Created by Joshua Schirra on 10/5/2021.
//

#pragma once

#include "../../definitions.h"
#include "../../main/application.h"

using namespace Rubix;

namespace Rubix::Menu {

    class Screen {
    public:
        virtual void init(int screenWidth, int screenHeight) {}

        virtual void render(int screenWidth, int screenHeight, int mouseX, int mouseY, double delta) {}

    };
}