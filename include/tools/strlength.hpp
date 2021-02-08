
// [2021-02-08] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_STRLENGTH_USED_
#define dTOOLS_STRLENGTH_USED_ 100
#include <tools/features.hpp>
#include <tools/assert.hpp>

//==============================================================================
//=== if_ ======================================================================
#ifndef dTOOLS_IF_USED_ 
#define dTOOLS_IF_USED_
namespace tools 
{
    template <bool, class ret> struct if_;
    template <class ret> struct if_<true, ret>
        { typedef ret type; };

} // namespace tools 
#endif // !dTOOLS_IF_USED_
//==============================================================================
//==============================================================================
namespace tools
{
    #define dATTRIBUTES \
        dNODISCARD dCONSTEXPR_CPP11

    #define dTEMPLATE \
        template<class s> dATTRIBUTES

    namespace stringed_v1
    {
        dTEMPLATE size_t strlen_pointer(s* text) dNOEXCEPT
        {
            dASSERT(text);
            const s* p = text;
            while (*p != 0)
                ++p;
            return static_cast<size_t>(p - text);
        }

        dTEMPLATE size_t strlength(s*& p)                dNOEXCEPT { return strlen_pointer(p); }
        dTEMPLATE size_t strlength(s* const& p)          dNOEXCEPT { return strlen_pointer(p); }
        dTEMPLATE size_t strlength(s* volatile& p)       dNOEXCEPT { return strlen_pointer(p); }
        dTEMPLATE size_t strlength(s* volatile const& p) dNOEXCEPT { return strlen_pointer(p); }

        dTEMPLATE size_t strlength(const s& text) dNOEXCEPT 
            { return text.length(); }

        template<class ch, size_t n>
        dATTRIBUTES
        size_t strlen_recursieve(const ch(&text)[n], const size_t beg) dNOEXCEPT
        {
            dASSERT(beg < n);
            namespace x = ::tools::stringed_v1;
            return text[beg] != 0 ?
                x::strlen_recursieve(text, beg + 1) :
                beg;
        }

        #define dEXPRESSION(...) \
            typename if_< (__VA_ARGS__), size_t >::type

        #define dSIZE_SMALL_ARRAY dEXPRESSION(n <  256)
        #define dSIZE_BIG_ARRAY   dEXPRESSION(n >= 256)

        template<class ch, size_t n>
        dATTRIBUTES
        dSIZE_SMALL_ARRAY strlength(ch (&text)[n]) dNOEXCEPT
        {
            namespace x = ::tools::stringed_v1;
            return x::strlen_recursieve(text, 0);
        }

        template<class ch, size_t n> 
        dATTRIBUTES
        dSIZE_BIG_ARRAY strlength(ch (&text)[n]) dNOEXCEPT
        { 
            for (size_t i = 0; i != n; ++i)
                if (text[i] == 0)
                    return i;
            assert(false && "tools::strlength: invalid null-terminator");
            return n;
        }

        #undef dEXPRESSION

    } // namespace stringed_v1

    #ifdef dHAS_CPP11
        dTEMPLATE size_t strlength(s&& text) dNOEXCEPT 
            { return ::tools::stringed_v1::strlength(text); }
    #else
        dTEMPLATE size_t strlength(const s& text) dNOEXCEPT 
        { 
            return ::tools::stringed_v1::strlength(text);
        }
    #endif // !dHAS_CPP11

    #undef dATTRIBUTES
    #undef dTEMPLATE

} // namespace tools 
//==============================================================================
//==============================================================================
#endif // !dTOOLS_STRLENGTH_USED_

