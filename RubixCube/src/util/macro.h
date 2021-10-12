//
// Created by Joshua Schirra on 10/4/2021.
//

#pragma once

#include "../config.h"
#include <iostream>
#include <stdexcept>
#include <string>

#define r_exception(x) throw std::runtime_error(x);

#ifndef NDEBUG
#define r_debug(x) std::cout << x << "\n";
#else
#define r_debug(x)
#endif
