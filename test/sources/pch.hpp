
// [2021-02-05] Idrisov Denis R.
// [2021-02-05] birthday of the project
#pragma once

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif

#ifdef _MSC_VER
    #define dMESSAGE(...)  __pragma(message(__VA_ARGS__))
#else
    #define dMESSAGE(...) 
#endif

//#include <tools/features.hpp>

#if !defined(_MSC_VER) || _MSC_VER > 1900
    //#pragma message("build for msvc2017 (or newer) or gcc-like compiler")
    #define dHAS_RVALUE_ARRAY
#endif

#ifdef _MSC_VER
    #include <tools/match/confbuild.hpp>

    #ifdef STABLE_RELEASE
        #pragma message("[test] tools/match: build stable release version")
    #else
        #pragma message("[test] tools/match: build development version")
    #endif

    #pragma message("[test] tools/match: " dFULL_VERSION)
    #pragma message("[test] tools/match: enabled -> pch")

    #ifdef _DLL
        #ifdef _DEBUG
            #pragma message("[test] tools/match: enabled -> MDd (debug-dynamic runtime c++)")
        #else
            #pragma message("[test] tools/match: enabled -> MD (release-dynamic runtime c++)")
        #endif
    #else
        #ifdef _DEBUG
            #pragma message("[test] tools/match: enabled -> MTd (debug-static runtime c++)")
        #else
            #pragma message("[test] tools/match: enabled -> MT (release-static runtime c++)")
        #endif
    #endif

    #ifdef dHAS_RVALUE_ARRAY
        #pragma message("[test] tools/match: enabled -> dHAS_RVALUE_ARRAY")
    #else
        #pragma message("[test] tools/match: disabled -> dHAS_RVALUE_ARRAY")
    #endif

#endif // !_MSC_VER

//================================================================================
//================================================================================

#include <mygtest/pch_used.hpp>

//================================================================================
//================================================================================

#ifdef NDEBUG
    #define dASSERT(...)
#else
    #include <cassert>
    #define dASSERT(...) assert(__VA_ARGS__)
#endif

//================================================================================
//================================================================================

