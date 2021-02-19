
// [2021y-02m-05d] Idrisov Denis R.
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

//===== tools/match ========== (pre11) (c++11) =============||==================
    #define TEST_TOOLS_MATCH_GROUP_EXTRA                    // ready!
    #define TEST_TOOLS_MATCH_GROUP_PLUS                     // ready!
    #define TEST_TOOLS_MATCH_GROUP                          // ready!
    #define TEST_TOOLS_MATCH_OPTIMIZE_MASK                  // ready!
    #define TEST_TOOLS_MATCH_PATTERN                        // ready!

//===== tools/types ========== (pre11) (c++11) =============||==================
    #define TEST_TOOLS_ENABLE_IF                            // ready!

//===== tools/stringed =============== (c++11) =============||==================
    #define TEST_TOOLS_STRINGED_CONCEPT                     // ready!
    #define TEST_TOOLS_STRINGED_STRLEN                      // ready!

//===== tools ================ (pre11) (c++11) =============||==================
    #define TEST_TOOLS_VALID                                // ready! 
    #define TEST_TOOLS_STRLENGTH                            // ready! 

//==============================================================================
//==============================================================================

#endif // !dTEST_STABLE_USED_

