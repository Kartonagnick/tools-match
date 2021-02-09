
// [2020y-09m-04d] Idrisov Denis R.
// [2021y-02m-08d] Idrisov Denis R.
//==============================================================================
//==============================================================================
#pragma once
#ifndef dTOOLS_ENABLE_IF_USED_
#define dTOOLS_ENABLE_IF_USED_ 100

#if (defined(_MSC_VER) && _MSC_VER >= 1800) || __cplusplus >= 201103L
    // #pragma message("build for msvc2013 (or newer)")
    // #pragma message("build for c++11 (or newer)")
    #define dHAS_USING_ALIAS 1
#endif

namespace tools
{
    template <bool, class = void>
    struct enable_if;

    template <class t> struct enable_if<true, t>
        { typedef t type; };

    #ifdef dHAS_USING_ALIAS
        template <bool ok, class t = void>
        using enable_if_t
            = typename enable_if<ok, t>::type;
    #endif

} // namespace tools

//==============================================================================
//==============================================================================
#endif // !dTOOLS_ENABLE_IF_USED_
