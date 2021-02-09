
// [2021y-02m-05d] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_STRLEN_USED_
#define dTOOLS_STRLEN_USED_ 100

#include <tools/assert.hpp>
#include <tools/features.hpp>
#include <tools/stringed/concept.hpp>

//==============================================================================
//=== if_ ======================================================================
#ifndef dTOOLS_IF_USED_ 
#define dTOOLS_IF_USED_
namespace tools 
{
    template <bool, class ret = void> struct if_;
    template <class ret> struct if_<true, ret>
        { typedef ret type; };

} // namespace tools 
#endif // !dTOOLS_IF_USED_
//==============================================================================
//==============================================================================
namespace tools 
{
    template<class s>
    dNODISCARD dCONSTEXPR_CPP11 auto strlen(s&& v) dNOEXCEPT 
    -> dSTRING_CONSEPT(size_t, v)
        { return v.length(); }

    template<class s>
    dNODISCARD dCONSTEXPR_CPP14 auto strlen(s&& v) dNOEXCEPT 
    -> dPOINTER_CONSEPT(size_t, v)
    { 
        dASSERT(v);
        const auto* p = v;
        while (*p != 0)
            ++p;
        return static_cast<size_t>(p - v);
    }

    namespace detail
    {
        template<class ch, size_t n>
        dNODISCARD dCONSTEXPR_CPP11
        size_t strlen_recursieve(const ch(&text)[n], const size_t beg) dNOEXCEPT
        {
            dASSERT(beg < n);
            namespace x = ::tools::detail;
            return text[beg] != 0 ?
                x::strlen_recursieve(text, beg + 1) :
                beg;
        }

    } // namespace detail

    #define dEXPRESSION(...) \
        typename ::tools::if_<(__VA_ARGS__), size_t>::type

    #define dSIZE_SMALL_ARRAY dEXPRESSION(n <  256)
    #define dSIZE_BIG_ARRAY   dEXPRESSION(n >= 256)

    template<class ch, size_t n>
    dNODISCARD dCONSTEXPR_CPP11
    dSIZE_SMALL_ARRAY strlen(ch (&text)[n]) dNOEXCEPT
    {
        namespace x = ::tools::detail;
        return x::strlen_recursieve(text, 0);
    }

    template<class ch, size_t n> 
    dNODISCARD dCONSTEXPR_CPP14
    dSIZE_BIG_ARRAY strlen(ch (&text)[n]) dNOEXCEPT
    { 
        for (size_t i = 0; i != n; ++i)
            if (text[i] == 0)
                return i;
        assert(false && "tools::str1::strlen: invalid null-terminator");
        return n;
    }

    #ifdef dHAS_RVALUE_ARRAY

        template<class ch, size_t n>
        dNODISCARD dCONSTEXPR_CPP11
        dSIZE_SMALL_ARRAY strlen(ch (&&text)[n]) dNOEXCEPT
            { return ::tools::strlen(text); }

        template<class ch, size_t n> 
        dNODISCARD dCONSTEXPR_CPP14
        dSIZE_BIG_ARRAY strlen(ch (&&text)[n]) dNOEXCEPT
            { return ::tools::strlen(text); }

    #endif // !dHAS_RVALUE_ARRAY

    #undef dSIZE_SMALL_ARRAY
    #undef dSIZE_BIG_ARRAY
    #undef dEXPRESSION

} // namespace tools 

//================================================================================
//================================================================================
#endif // !dTOOLS_STRLEN_USED_

