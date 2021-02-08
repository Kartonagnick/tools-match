
// [2021-02-05] Idrisov Denis R.
#pragma once

#ifndef dTOOLS_MATCH_OPTIMIZE_MASK_USED_ 
#define dTOOLS_MATCH_OPTIMIZE_MASK_USED_ 1

#include <tools/match/details.hpp>

//==============================================================================
//=== declaration ==============================================================
namespace tools
{
    // return new length
    template<class ch> 
    size_t optimize_mask(ch* const mask, const size_t len) noexcept;

    // return new length
    template<class str> 
    size_t optimize_mask(str& mask) noexcept;

} // namespace tools
//==============================================================================
//==============================================================================




//=== implementation ===========================================================
namespace tools
{
    // return new length
    template<class ch> 
    size_t optimize_mask(ch* const mask, const size_t len) noexcept
    {
        assert(mask);

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
        assert(len > delta);
        return len - delta;
    }

    namespace detail
    {
        template<class s, dSTRING_CONSEPT(s)> 
        size_t optimize_mask(s&& mask) noexcept 
        {
            const size_t len
                = ::tools::optimize_mask(&mask[0], mask.length());
            mask.resize(len);
            return mask.length();
        }

        template<class s>
        auto optimize_mask(s&& mask)
        dPOINTER_OR_ARRAY_CONSEPT(mask, size_t)
        {
            assert(::tools::valid_(mask));
            const size_t len = ::tools::length_(mask);
            return ::tools::optimize_mask(&mask[0], len);
        }

    } // namespace detail

    // return new length
    template<class str> 
    size_t optimize_mask(str& mask) noexcept
    {
        assert(::tools::valid_(mask));
        using x = ::std::remove_reference_t<str>;
        using z = ::std::remove_pointer_t<x>;
        static_assert(
            !::std::is_const<z>::value,
            "expected non-const object"
        );
        return ::tools::detail::optimize_mask(mask);
    }

} // namespace tools
//==============================================================================
//==============================================================================
#endif // !dTOOLS_MATCH_OPTIMIZE_MASK_USED_



