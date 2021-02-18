
// [2021y-02m-05d] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_FEATURES_USED_
#define dTOOLS_FEATURES_USED_ 101

//==============================================================================
//=== dMESSAGE =================================================================

#ifdef _MSC_VER
    #define dMESSAGE(...)  __pragma(message(__VA_ARGS__))
#else
    #define dMESSAGE(...) 
#endif

//==============================================================================
//=== dHAS_RVALUE_REFERENCES ===================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1700
    // #pragma message("build for msvc2010 (or newer) or other compiler")
    #define dHAS_RVALUE_REFERENCES 1
#endif
    
//==============================================================================
//=== dHAS_CPP11 ===============================================================

#if (defined(_MSC_VER) && _MSC_VER >= 1900) || __cplusplus >= 201103L
    // #pragma message("build for msvc2015 (or newer) or other compiler")
    // #pragma message("build for c++11 (or newer)")
    #define dHAS_CPP11 1
    #define dHAS_CONSTEXPR_CPP11 1
    #define dCONSTEXPR_CPP11 constexpr
#else 
    #define dCONSTEXPR_CPP11 inline
#endif

#ifdef dHAS_CPP11
    using nullptr_t = decltype(nullptr);
#endif

//==============================================================================
//=== dHAS_DELETING_FUNCTIONS ==================================================

#if (defined(_MSC_VER) && _MSC_VER >= 1800) || __cplusplus >= 201103L
    // #pragma message("build for msvc2013 (or newer) or other compiler")
    // #pragma message("build for c++11 (or newer)")
    #define dHAS_TEMPLATE_FUNCTION_DEFAULT_PARAM 1
    #define dHAS_DELETING_FUNCTIONS 1
    #define dHAS_USING_ALIAS 1
#endif

#ifdef dHAS_DELETING_FUNCTIONS
    #define dNOCOPYABLE(Class)                   \
        Class(const Class&)            = delete; \
        Class(Class&&)                 = delete; \
        Class& operator=(const Class&) = delete; \
        Class& operator=(Class&&)      = delete
#else
    #define dNOCOPYABLE(Class) \
        Class(const Class&);   \
        Class& operator=(const Class&)
#endif

//==============================================================================
//=== dNOEXCEPT ================================================================

#if defined(__clang__)
    #if __has_feature(cxx_noexcept)
        #define dHAS_NOEXCEPT 1
    #endif
#endif

#if defined(__GXX_EXPERIMENTAL_CXX0X__) && __GNUC__ * 10 + __GNUC_MINOR__ >= 46
    #define dHAS_NOEXCEPT 1
#endif

#if defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 190023026
    // #pragma message("build for msvc2015 (or newer)")
    #define dHAS_NOEXCEPT 1
#endif
                
#ifdef dHAS_NOEXCEPT
    #define dNOEXCEPT noexcept
#else
    #define dNOEXCEPT throw()
#endif

//==============================================================================
//=== dCONSTEXPR_CPP14 =========================================================

#if (defined(_MSC_VER) && _MSC_VER > 1900) || __cplusplus >= 201402L
    // #pragma message("build for msvc2017 (or newer) or other compiler")
    // #pragma message("build for c++14 (or newer)")
    #define dCONSTEXPR_CPP14 constexpr
    #define dHAS_CONSTEXPR_CPP14 1
    #define dHAS_CPP14 1
#else
    #define dCONSTEXPR_CPP14 inline
#endif

//==============================================================================
//=== dHAS_RVALUE_ARRAY ========================================================

#if !defined(_MSC_VER) || _MSC_VER > 1900
    //#pragma message("build for msvc2017 (or newer) or gcc-like compiler")
    #define dHAS_RVALUE_ARRAY 1
#endif

//==============================================================================
//=== dNODISCARD ===============================================================

#if (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L
    // #pragma message("build for c++17 (or newer))
    #define dHAS_CPP17 1
    #define dNODISCARD [[nodiscard]]
#else
    #define dNODISCARD
#endif

//==============================================================================
//==============================================================================
#endif // !dTOOLS_FEATURES_USED_

// trailing-syntaxis-for-auto (since C++11)
// example: auto foo() -> int
