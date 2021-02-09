
// [2021y-02m-05d] Idrisov Denis R.
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

//===== tools/match ========== (pre11) (c++11) =============||==================
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

// in progress...

#endif // !dTEST_DEVELOP_USED_
