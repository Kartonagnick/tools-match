
// [2021-02-05] Idrisov Denis R.
#pragma once

#ifndef dTOOLS_MATCH_PATTERN_USED_ 
#define dTOOLS_MATCH_PATTERN_USED_ 100

#include <tools/match/details.hpp>

//==============================================================================
//=== match_pattern ============================================================

namespace tools
{
    template<class s1, class s2>
    dNODISCARD bool match_pattern(
        const s1& text,
        const s2& pattern
    ) dNOEXCEPT;

    template<class ch>
    dNODISCARD bool match_pattern(
        const ch* s, 
        const ch* p
    ) dNOEXCEPT;

    template<class s1, class s2, class container>
    dNODISCARD bool match_pattern(
        const s1& text, 
        const s2& pattern, 
        container& dst
    );

} // namespace tools

//==============================================================================
//==============================================================================




//==============================================================================
//=== implementation ===========================================================

namespace tools
{
    template<class ch>
    dNODISCARD bool match_pattern(const ch* s, const ch* p) dNOEXCEPT
    {
        dASSERT(s);
        dASSERT(p);

        const ch star = '*';
        const ch qust = '?';

        const ch* rs = NULL;
        const ch* rp = NULL;

        for(;;)
        {
            if(*p == star)
            {
                rs = s; 
                rp = ++p;
            }
            else if (!*s)
            {
                return !*p;
            }
            else if(*s == *p || *p == qust)
            {
                ++s;
                ++p;
            }
            else if(rs)
            {
                s = ++rs; 
                p = rp;
            }
            else
                return false;
        }
    }

    template<class s1, class s2>
    dNODISCARD bool match_pattern(const s1& text, const s2& pattern) dNOEXCEPT
    {
        dASSERT(::tools::valid(text));
        dASSERT(::tools::valid(pattern));
        return ::tools::match_pattern(
            &text[0], &pattern[0]
        );
    }

} // namespace tools

//==============================================================================
//==============================================================================

#include <tools/match/pattern_cont.hpp>

//==============================================================================
//==============================================================================
#endif // !dTOOLS_MATCH_PATTERN_USED_



