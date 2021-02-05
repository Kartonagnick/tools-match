
#pragma once
#ifndef dTEST_DEVELOP_USED_ 
#define dTEST_DEVELOP_USED_ 1

#ifdef STABLE_RELEASE
    #error STABLE_RELEASE require #include <test-stable.hpp>
#endif

    #define CODE_GENERATION_ON
    #define INCLUDE_AUTO_GENERATED

    // #define INCLUDE_STRESS_TESTS
    #define INCLUDE_LONG_LONG_TESTS
    #define INCLUDE_LONG_TESTS

//==============================================================================
//===== modern/classic =====================================||==================
    #define TEST_MODERN                                     // ready!
    #define TEST_CLASSIC                                    // ready!
//==============================================================================
//==============================================================================
// in progress...

#endif // !dTEST_DEVELOP_USED_
