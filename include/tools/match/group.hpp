
// [2021y-02m-05d] Idrisov Denis R.
#pragma once

#ifndef dTOOLS_MATCH_GROUP_
#define dTOOLS_MATCH_GROUP_ 100
//==============================================================================
//==============================================================================

#include <tools/match/details.hpp>

namespace tools
{
    // assert(!me::match_group("symbol", ""    ));
    // assert( me::match_group(""      , ""    ));
    // assert(!me::match_group(""      , "mask"));

    template<class str1, class str2>
    dNODISCARD 
    bool match_group(const str1& symbol, const str2& mask) dNOEXCEPT;

} // namespace tools

//==============================================================================
//==============================================================================
namespace tools
{
    namespace detail_match_group
    {
        template<class ch> 
        bool check_template(const ch* expr, const ch* group) dNOEXCEPT
        {
            dASSERT(expr);
            dASSERT(group);

            if (!expr || !group) 
                return false;

            const ch *mask_ast = 0;
            const ch *mask = expr;
            bool ast = false;

            while (*mask == '+' || *mask == '!')
            {
                assert(false && "check_template: unexpected characters");
                ++mask;
            }

            //--- check for '*' at start
            for (; *mask && *mask == '*'; ++mask)
                mask_ast = mask,
                ast = true;
        
            //--- group loop
            for (; *group && *mask; ++group) 
            {
                //--- check symbols
                if (*group != *mask) 
                {
                    if (!ast) 
                        return false;
                    else
                        continue; 
                }
                //--- check word
                for (; *mask && *mask != '*' && *group; ++mask, ++group) 
                    if (*group != *mask)
                    {
                        if (!ast) 
                            return false;
                        else 
                        {
                            mask = mask_ast;
                            break;
                        }
                    }

                //--- check group
                if (*mask == 0 && *group == 0) 
                    return true;

                if (*mask == 0) 
                {
                    if (!ast) 
                        return false;
                    else 
                        mask = mask_ast; 
                }
                if (*group == 0)
                {
                    if (*mask && *mask != '*') 
                        return false; 
                    else 
                    {
                        while (*mask == '*')
                            ++mask;
                        if (*mask == 0) 
                            return true;
                        return false;
                    }
                }
                else 
                {
                    for (; *mask && *mask == '*'; ++mask)
                        mask_ast = mask;
                
                    if (*mask == 0) 
                        return true;
                    ast = true;
                    --group;
                }
            }
            //--- mask empty?
            if (*mask) 
                return false;
            return true;
        }
    
        enum eRESULT { eMATCHED, eNO_MATCHED, eBANNED };

        template<class ch>
        eRESULT match_group(const ch* symbol, const ch* masks) dNOEXCEPT
        {
            namespace x = ::tools::detail_match_group;

            dASSERT(symbol);
            dASSERT(masks);
            dASSERT(*symbol != ' ');

            //--- check
            if (!masks || !symbol) 
                return x::eNO_MATCHED;

            if(*symbol == 0 && *masks == 0)
                return x::eMATCHED;

            ch mask [256];
            bool found = false;

            //--- look through groupmask
            for (const ch* token = masks; *token != 0; ++token)
            {
                //--- skip spaces and commas
                if (*token == ' ' || *token == ',') 
                    continue;

                //--- copy mask
                size_t pos = 0;
                for (pos = 0; *token != 0 && *token != ',' && pos < 255; ++token, ++pos)
                    mask[pos] = *token;
        
                //--- skip spaces and commas
                while (pos > 0 && (mask[pos - 1] == ' ' || mask[pos - 1] == ',')) 
                    --pos;

                mask[pos] = 0;

                //--- check
                const ch* p = mask;
                bool negative = false;
                bool especial = false;
                for (;;)
                {
                    if (*p == '+')
                        especial = true;
                    else if (*p == '!')
                        negative = true;
                    else
                        break;
                    ++p;
                }
                
                const bool ok = x::check_template(p, symbol);
                if (ok)
                {
                    if(negative)
                        return x::eBANNED;
                    if(especial)
                        return x::eMATCHED;
                    found = true;
                }

                //--- template over
                if (!*token)
                    break;
            }
            //--- return result
            return found? x::eMATCHED: x::eNO_MATCHED;
        }

        #ifndef NDEBUG // debug
        template<class ch> 
        void check_symbol(ch* symbol, const size_t len) dNOEXCEPT
        {
            assert(symbol);
            const ch* front = &symbol[0];
            const ch* back = front + len - 1;
            assert(*front != ' ');
            assert(*back  != ' ');
        }
        #endif // !!NDEBUG

    } // namespace detail_match_group

//==============================================================================
//==============================================================================

    template<class str1, class str2>
    dNODISCARD
    bool match_group(const str1& symbol, const str2& mask) dNOEXCEPT
    {
        namespace x = detail_match_group;
        #ifndef NDEBUG // debug
            const size_t len_symbol = ::tools::strlength(symbol);
            const size_t len_mask   = ::tools::strlength(mask);
            dASSERT(len_symbol < 255);
            dASSERT(len_mask   < 255);
            if(len_symbol != 0)
                x::check_symbol(&symbol[0], len_symbol);
        #endif

        const x::eRESULT result
            = x::match_group(&symbol[0], &mask[0]);

        return result == x::eMATCHED;
    }

    #if 0
    // --- todo
    template<class s1, class s2>
    bool match_group(const s1& symbol, const s2& security, const str_t& mask) noexcept
    {
        if(tools::match_group(symbol, mask))
        {
            if(tools::match_group(security, mask + ", *"))
                return true;
        }
        else
        {
            if(tools::match_group(security, mask))
            {
                if(tools::match_group(symbol, mask + ", *"))
                    return true;
            }
        }
        return false;
    }
    #endif

} // namespace tools

//==============================================================================
//==============================================================================
#endif // !dTOOLS_MATCH_GROUP_

