
// [2021-02-05] Idrisov Denis R.
#pragma once

#ifndef dTEST_STABLE_USED_ 
#define dTEST_STABLE_USED_ 1

#ifndef STABLE_RELEASE
    #error #include <test-stable.hpp> require #define STABLE_RELEASE
#endif

    #define dFORBID_ZERO_SIZE_ARRAY
    #define INCLUDE_AUTO_GENERATED

    // #define INCLUDE_STRESS_TESTS
    #define INCLUDE_LONG_LONG_TESTS
    #define INCLUDE_LONG_TESTS

//==============================================================================
//===== modern/classic =====================================||==================
    #define TEST_MODERN                                     // ready!
    #define TEST_CLASSIC                                    // ready!
//===== tools ==============================================||==================
    #define TEST_TOOLS_VALID                                // ready!
//==============================================================================
//==============================================================================

#endif // !dTEST_STABLE_USED_

