
#pragma once

#ifdef _MSC_VER
    #include <tools/match/confbuild.hpp>
    #pragma message("tools/match: pch -> enabled")
    #pragma message("tools/match: " dFULL_VERSION)

    #ifdef STABLE_RELEASE
        #pragma message("Build stable release version")
    #else
        #pragma message("Build development version")
    #endif
#endif




