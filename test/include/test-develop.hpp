
// [2021-02-05] Idrisov Denis R.
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
    // #define TEST_MODERN                                  // ready!
    // #define TEST_CLASSIC                                 // ready!

//===== tools ==============================================||==================
    // support pre11 and c++11
    #define TEST_TOOLS_VALID                                // ready! 
    #define TEST_TOOLS_STRLENGTH                            // ready! 

//===== tools/stringed =====================================||==================
    // need c++11
    #define TEST_TOOLS_STRINGED_CONCEPT                     // ready!
    #define TEST_TOOLS_STRINGED_STRLEN                      // in progress...

//===== tools/match ========================================||==================
    // #define TEST_TOOLS_MATCH_GROUP                       // ready!
    // #define TEST_TOOLS_MATH_OPTIMIZE_MASK                // ready!
    // #define TEST_TOOLS_MATCH_PATTERN                     // ready!

//==============================================================================
//==============================================================================
// in progress...

#endif // !dTEST_DEVELOP_USED_
