
// [2021y-02m-07d] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_ASSERT_USED_
#define dTOOLS_ASSERT_USED_ 100
//==============================================================================
//==============================================================================

#ifdef NDEBUG
    #define dASSERT(...)
#else
    #include <cassert>
    #define dASSERT(...) assert(__VA_ARGS__)
#endif

//==============================================================================
//==============================================================================
#endif // !dTOOLS_ASSERT_USED_
