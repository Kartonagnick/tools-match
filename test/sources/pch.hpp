
#pragma once

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif

#ifdef _MSC_VER
    #include <tools/match/confbuild.hpp>
    #pragma message("[test] tools/match: pch -> enabled")
    #pragma message("[test] tools/match: " dFULL_VERSION)

    #ifdef STABLE_RELEASE
        #pragma message("Build stable release version")
    #else
        #pragma message("Build development version")
    #endif
#endif

//================================================================================
//================================================================================

#include <mygtest/pch_used.hpp>

//================================================================================
//================================================================================

#include <cassert>
