
// [2021-02-05] Idrisov Denis R.
#pragma once
#include <tools/features.hpp>
//==============================================================================
//==============================================================================

#ifdef _MSC_VER
    #define dMESSAGE(...)  __pragma(message(__VA_ARGS__))
#else
    #define dMESSAGE(...) 
#endif

//==============================================================================
//==============================================================================

#include <cassert>
#include <string>

namespace staff
{
    typedef ::std::string  str_t;
    typedef ::std::wstring str_w;
    typedef ::std::basic_string<int> str_i;

    template<class t> t* maket_pointer(const t*)                dNOEXCEPT;
    template<class t> t* maket_pointer(const t* const)          dNOEXCEPT;
    template<class t> t* maket_pointer(const t* volatile)       dNOEXCEPT;
    template<class t> t* maket_pointer(const t* volatile const) dNOEXCEPT;

} // namespace staff

//==============================================================================
//==============================================================================
