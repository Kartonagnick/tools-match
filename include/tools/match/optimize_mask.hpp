
// [2021y-02m-05d] Idrisov Denis R.
#pragma once

#ifndef dTOOLS_MATCH_OPTIMIZE_MASK_USED_ 
#define dTOOLS_MATCH_OPTIMIZE_MASK_USED_ 100

#include <tools/match/details.hpp>

//==============================================================================
//=== declaration ==============================================================
namespace tools
{
    // return new length
    template<class ch> 
    dNODISCARD size_t optimize_mask(ch* const mask, const size_t len) dNOEXCEPT;

    // return new length
    template<class str> 
    dNODISCARD size_t optimize_mask(str& mask) dNOEXCEPT;

} // namespace tools
//==============================================================================
//==============================================================================




//=== implementation ===========================================================
namespace tools
{
    // return new length
    template<class ch> 
    dNODISCARD size_t optimize_mask(ch* const mask, const size_t len) dNOEXCEPT
    {
        dASSERT(mask);

        if(len == 0)
            return 0;

        size_t delta = 0;

        // --- ищем две идущих подряд звезды
        size_t i = 0;
        for(; i != len - 1; ++i)
        {
            if(mask[i] == '*' && mask[i + 1] == '*')
                break;
        }

        if(i == len - 1)
            return len;

        // --- сдвигаем влево
        ++delta;
        bool star = true;
        size_t t = (++i);
        for(++i; i != len; ++i)
        {
            if(mask[i] != '*')
                star = false;
            else if(star)
            {
                ++delta;
                continue;
            }
            else
                star = true;

            mask[t] = mask[i];
            mask[i] = '\0';
            ++t;
        }
        dASSERT(len > delta);
        return len - delta;
    }

    namespace detail
    {
        template<class s> 
        size_t optimize_mask(s& mask) dNOEXCEPT 
        {
            const size_t len
                = ::tools::optimize_mask(&mask[0], mask.length());
            mask.resize(len);
            return mask.length();
        }

        template<class s>
        size_t optimize_mask_pointer(s* mask) dNOEXCEPT
        {
            assert(mask);
            const size_t len = ::tools::strlength(mask);
            return ::tools::optimize_mask(&mask[0], len);
        }

        template<class s>
        size_t optimize_mask(s*& p) dNOEXCEPT 
            { return optimize_mask_pointer(p); }

        template<class s> 
        size_t optimize_mask(s* const& p) dNOEXCEPT 
            { return optimize_mask_pointer(p); }

        template<class s> 
        size_t optimize_mask(s* volatile& p) dNOEXCEPT 
            { return optimize_mask_pointer(p); }

        template<class s> 
        size_t optimize_mask(s* volatile const& p) dNOEXCEPT 
            { return optimize_mask_pointer(p); }

        template<class ch, size_t n> 
        size_t optimize_mask(ch (&arr)[n]) dNOEXCEPT 
            { return optimize_mask_pointer(arr); }

    } // namespace detail

    // return new length
    template<class str> 
    dNODISCARD size_t optimize_mask(str& mask) dNOEXCEPT
    {
        dASSERT(::tools::valid(mask));
        #ifdef dHAS_CPP11
            using x = ::std::remove_reference_t<str>;
            using z = ::std::remove_pointer_t<x>;
            static_assert(
                !::std::is_const<z>::value,
                "expected non-const object"
            );
        #endif
        return ::tools::detail::optimize_mask(mask);
    }

} // namespace tools
//==============================================================================
//==============================================================================
#endif // !dTOOLS_MATCH_OPTIMIZE_MASK_USED_



