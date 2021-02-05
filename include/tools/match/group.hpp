
#pragma once

#ifndef dTOOLS_MATCH_GROUP_
#define dTOOLS_MATCH_GROUP_ 1

#include <tools/match/details.hpp>

namespace tools
{
    // assert(!me::match_group("symbol", ""    ));
    // assert( me::match_group(""      , ""    ));
    // assert(!me::match_group(""      , "mask"));

    template<class str1, class str2>
    bool match_group(const str1& symbol, const str2& mask) noexcept;

} // namespace tools

//==============================================================================
//==============================================================================
namespace tools
{
    namespace detail
    {
        template<class ch> 
        bool check_template(ch* expr, const ch* group) noexcept
        {
            assert(expr);
            assert(group);

            if (!expr || !group) 
                return false;

            ch *mask     = nullptr;
            ch *mask_ast = nullptr;
            bool ast     = false;

            //--- skip multiple '!'
            for (mask = expr; *mask == '!'; ++mask)
                { /*nothing*/ }

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
                if (!*mask && !*group) 
                    return true;

                if (!*mask) 
                {
                    if (!ast) 
                        return false;
                    else 
                        mask = mask_ast; 
                }
                if (!*group)
                {
                    if (*mask && *mask != '*') 
                        return false; 
                    else 
                    {
                        for (; *mask && *mask == '*'; ++mask) 
                            { /* nothing */ }
                        if (!*mask) 
                            return true;
                        return false;
                    }
                }
                else 
                {
                    for (; *mask && *mask == '*'; ++mask)
                        mask_ast = mask;
                
                    if (!*mask) 
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
    
        template<class ch>
        bool match_group(const ch* symbol, const ch* masks) noexcept
        {
            assert(symbol);
            assert(masks);
            assert(*symbol != ' ');

            //--- check
            if (!masks || !symbol) 
                return false;

            if(*symbol == 0 && *masks == 0)
                return true;

            enum { eMAX_MASK_SIZE = 256 };
            ch mask [eMAX_MASK_SIZE] = {};
            bool found = false;
            int pos = 0;

            //--- look through groupmask
            for (const ch* token = masks; *token; ++token)
            {
                //--- skip spaces and commas
                if (*token == ' ' || *token == ',') 
                    continue;
                //--- copy mask
                for (pos = 0; *token && *token != ',' && pos < 255; ++token, ++pos)
                    mask[pos] = *token;
        
                //--- skip spaces and commas
                while (pos > 0 && (mask[pos - 1] == ' ' || mask[pos - 1] == ',')) 
                    --pos;

                mask[pos] = 0;

                //--- check
                const bool ok = detail::check_template(mask, symbol);
                if (mask[0] == '!' && ok)
                    return false;
                else if(ok)
                    found = true;

                //--- template over
                if (!*token)
                    break;
            }
            //--- return result
            return found;
        }

    } // namespace detail

//==============================================================================
//==============================================================================

    template<class str1, class str2>
    bool match_group(const str1& symbol, const str2& mask) noexcept
    {
        #ifndef NDEBUG
            // debug
            namespace x = ::tools;
            const auto len_symbol = x::length_(symbol);
            const auto len_mask   = x::length_(mask);
            assert(len_symbol < 255);
            assert(len_mask   < 255);

            if(len_symbol != 0)
            {
                const auto* front = &symbol[0];
                const auto* back = front + len_symbol - 1;
                assert(*front != ' ');
                assert(*back  != ' ');
            }
        #endif

        return detail::match_group(&symbol[0], &mask[0]);
    }

#if 0
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


#endif // !dTOOLS_MATCH_GROUP_

