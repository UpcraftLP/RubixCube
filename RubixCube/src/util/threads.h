//
// Created by Joshua Schirra on 10/5/2021.
//

#pragma once

#include "../definitions.h"
#include <windows.h>
#include <processthreadsapi.h>

namespace Rubix::Util {

    void setThreadName(std::wstring &&name) {
        // https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-setthreaddescription
        auto hResult = SetThreadDescription(GetCurrentThread(), name.c_str());
        if (FAILED(hResult)) {
            r_debug("Unable to set thread name!");
        }
    }
}