
#pragma once

#ifndef dTOOLS_MATCH_REGEX_USED_ 
#define dTOOLS_MATCH_REGEX_USED_ 1

#include <cassert>
#include <string>
#include <regex>

//==============================================================================
//=== declaration ==============================================================
namespace tools
{
    template<class s1, class s2>
    bool match_by_filemask(
        const s1& text, 
        const s2& pattern, 
        bool caseSensitive = false
    );

} // namespace tools

//==============================================================================
//=== implementation ===========================================================
namespace tools
{
    template<class t> 
    using degradate = ::std::remove_cv_t<
        ::std::remove_reference_t<t> 
    >;

    namespace detail_regex
    {
        template<class s> 
        void replace_all(s& src_txt, const s& old_txt, const s& new_txt)
        {
            size_t index = 0;
            while (true) 
            {
                 index = src_txt.find(old_txt, index);
                 if (index == s::npos)
                     break;

                 src_txt.replace(index, old_txt.size(), new_txt);
                 index += new_txt.size();
            }
        }

        inline void escape_regex(::std::string& regex)
        {
            using str_t = ::std::string;
            namespace me = ::tools::detail_regex;
            me::replace_all<str_t>(regex, "\\", "\\\\");
            me::replace_all<str_t>(regex, "^" , "\\^" );
            me::replace_all<str_t>(regex, "." , "\\." );
            me::replace_all<str_t>(regex, "$" , "\\$" );
            me::replace_all<str_t>(regex, "|" , "\\|" );
            me::replace_all<str_t>(regex, "(" , "\\(" );
            me::replace_all<str_t>(regex, ")" , "\\)" );
            me::replace_all<str_t>(regex, "{" , "\\{" );
            me::replace_all<str_t>(regex, "{" , "\\}" );
            me::replace_all<str_t>(regex, "[" , "\\[" );
            me::replace_all<str_t>(regex, "]" , "\\]" );
            me::replace_all<str_t>(regex, "*" , "\\*" );
            me::replace_all<str_t>(regex, "+" , "\\+" );
            me::replace_all<str_t>(regex, "?" , "\\?" );
            me::replace_all<str_t>(regex, "/" , "\\/" );
                           
            me::replace_all<str_t>(regex, "\\?", "."  );
            me::replace_all<str_t>(regex, "\\*", ".*" );
        }

        inline void escape_regex(::std::wstring& regex)
        {
            using str_w = ::std::wstring;
            namespace me = ::tools::detail_regex;
            me::replace_all<str_w>(regex, L"\\", L"\\\\");
            me::replace_all<str_w>(regex, L"^" , L"\\^" );
            me::replace_all<str_w>(regex, L"." , L"\\." );
            me::replace_all<str_w>(regex, L"$" , L"\\$" );
            me::replace_all<str_w>(regex, L"|" , L"\\|" );
            me::replace_all<str_w>(regex, L"(" , L"\\(" );
            me::replace_all<str_w>(regex, L")" , L"\\)" );
            me::replace_all<str_w>(regex, L"{" , L"\\{" );
            me::replace_all<str_w>(regex, L"{" , L"\\}" );
            me::replace_all<str_w>(regex, L"[" , L"\\[" );
            me::replace_all<str_w>(regex, L"]" , L"\\]" );
            me::replace_all<str_w>(regex, L"*" , L"\\*" );
            me::replace_all<str_w>(regex, L"+" , L"\\+" );
            me::replace_all<str_w>(regex, L"?" , L"\\?" );
            me::replace_all<str_w>(regex, L"/" , L"\\/" );
                           
            me::replace_all<str_w>(regex, L"\\?", L"."  );
            me::replace_all<str_w>(regex, L"\\*", L".*" );
        }


    } // namespace detail_regex

    template<class s1, class s2>
    bool match_by_filemask(
        const s1& text, 
        const s2& pattern, 
        bool caseSensitive)
    {
        namespace me = ::tools::detail_regex;
        using ch = degradate<decltype(pattern[0])>;
        using str_t = ::std::basic_string<ch>;

        constexpr ch beg = ch('^');
        constexpr ch end = ch('$');

        str_t tmp = pattern;
        me::escape_regex(tmp);
        const auto wild = beg + tmp + end;

        const auto mode = caseSensitive ? 
            ::std::regex::basic : 
            ::std::regex::icase
        ;

        const ::std::regex validator(wild, mode);
        return ::std::regex_match(text, validator);
    }

} // namespace tools

//==============================================================================

#endif // !dTOOLS_MATCH_REGEX_USED_



