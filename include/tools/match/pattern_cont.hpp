
// [2021-02-05] Idrisov Denis R.
#pragma once

#ifndef dTOOLS_MATCH_PATTERN_USED_ 
#define dTOOLS_MATCH_PATTERN_USED_ 1

#include <cassert>
#include <type_traits>

//#include <tools/stringed/stringed.hpp>
//#include <tools/stringed/basic.hpp>

//==============================================================================
//=== declaration ==============================================================
namespace tools
{
    template<class s1, class s2>
        bool match_pattern(const s1& text, const s2& pattern) noexcept;

    template<class s1, class s2, class container>
        bool match_pattern(const s1& text, const s2& pattern, container& dst);

    // return new length
    template<class ch> 
        size_t optimize_mask(ch* const mask, const size_t len) noexcept;

    // return new length
    template<class str> 
        size_t optimize_mask(str& mask);

} // namespace tools
//==============================================================================
//==============================================================================



//=== match_pattern(const s1& text, const s2& pattern) =========================
namespace tools
{
    namespace detail
    {
        template<class ch>
        bool match_pattern(const ch* s, const ch* p) noexcept
        {
            assert(s);
            assert(p);

            const ch* rs = nullptr;
            const ch* rp = nullptr;

            while (true)
                if (*p == '*')
                    rs = s,
                    rp = ++p;
                else if (!*s)
                    return !*p;
                else if (*s == *p || *p == '?')
                    ++s, 
                    ++p;
                else if (rs)
                    s = ++rs, 
                    p = rp;
                else
                    return false;
        }

    }//namespace detail

    template<class s1, class s2>
    bool match_pattern(const s1& text, const s2& pattern) noexcept
    {
        return detail::match_pattern(&text[0], &pattern[0]);
#if 0
        namespace me = ::tools;
        //drequired_compatible(s1, text, s2, pattern);
        return detail::match_pattern(
            me::c_str(text), 
            me::c_str(pattern)
        );
#endif
    }

} // namespace tools


//=== container& destination: implementation ===================================
namespace tools
{
    namespace detail
    {
        template<class ch>
        size_t offset(ch* const& last, ch* const& start) noexcept
        {
            assert(last >= start);
            return static_cast<size_t>(last - start);
        }

        template<class container>
        class has_operator_asccess
        {
            template <class type> static 
                ::std::true_type check(
                    ::std::add_pointer_t<decltype(::std::declval<type>()[0])>
                );

            template <class c> static 
                ::std::false_type check(...);
        public:
            has_operator_asccess() = delete;
           ~has_operator_asccess() = delete;

            using type 
                = decltype(check<container>(nullptr));

            enum { value = type::value };
        };

        // --- ::std::vector::operator[]
        // --- update iterator after realoc
        template<class container, class ch>
        ::std::enable_if_t< has_operator_asccess<container>::value >
        add_value_(
            container& dst, const ch* const s, 
            typename container::const_iterator& iter
        )
        {
            const auto v = ::std::distance(dst.cbegin(), iter);
            dst.emplace_back(s, 1);
            iter = dst.cbegin() + v;
        }
      
        // --- ::std::list
        // --- does not need to be updated iterator
        template<class container, class ch>
        ::std::enable_if_t< !has_operator_asccess<container>::value >
        add_value_(container& dst, const ch* const s, 
            typename container::const_iterator& iter
        )
        {
            dst.emplace_back(s, 1);
            (void) iter;
        }

        template<class ch, class container>
        bool match_pattern(
            const ch*    text, 
            const size_t lentext, 
            const ch*    mask, 
            const size_t lenmask, 
            container&   dst) 
        {
            using str_type 
                = typename container::value_type;

            using char_t 
                = typename str_type::value_type;

            using iter_t 
                = typename container::const_iterator;

            static_assert(
                !::std::is_const<container>::value,
                "[ERROR] 'container' can not be const"
            );

            static_assert(
                ::std::is_same<ch, char_t>::value,
                "symbols are not compatible"
            );

            namespace me = ::tools;
            
            assert(text);
            assert(mask);
            assert(me::length(text) >= lentext);
            assert(me::length(mask) >= lenmask);

            if(*text == '\0' && *mask == '\0')
                return true;

            const ch* st  = text;
            const ch* s   = text;
            const ch* pst = mask;
            const ch* p   = mask;

            const ch* rs = nullptr;
            const ch* rp = nullptr;

            dst.clear();

            iter_t iter = dst.cend();
            
            size_t curlen = 0;
            bool is_question = false;
            bool is_star     = false;

            while(true)
            {
                const auto dist = offset(p, pst);
                assert(p && dist <= lenmask);
                if(dist < lenmask  && *p=='*')
                {
                    rs = s;
                    rp = ++p;
                    if(!is_star)
                    {
                        dst.emplace_back();
                        iter = dst.end();
                        --iter;
                    }
                    is_star = true;                    
                    continue;
                }

                is_star = false;

                if(lentext == curlen)
                {
                    const size_t lenmask_ = offset(p, pst);
                    const auto success = lenmask_ == lenmask;
                    if(!success)
                        dst.clear();
                    return success;
                }

                bool next = false;
                if(*p=='?')
                {
                    if(!is_question)
                    {
                        is_question = true;
                        add_value_(dst, s, iter);
                    }
                    else
                    {
                        if(dst.empty())
                            add_value_(dst, s, iter);
                        else
                            dst.back() += *s;
                    }
                    next = true;
                }
                else if(*s==*p)
                {
                    is_question = false;
                    next = true;
                }

                if(next)
                {
                    ++s;
                    ++p;
                    ++curlen;
                    continue;
                }
           
                if(rs)
                {
                    assert(!dst.empty());
                    is_question = false;
                    str_type actual = *iter;
                    actual += *rs;
                    dst.erase(iter, dst.cend());
                    dst.emplace_back(std::move(actual));

                    iter = dst.cend(); 
                    --iter;

                    s = ++rs;
                    p = rp;

                    curlen = s - st;
                    continue;
                }
                else
                {
                    dst.clear();
                    return false;
                }
            }
        }

    }//namespace detail

    template<class s1, class s2, class container>
    bool match_pattern(
        const s1& text, 
        const s2& pattern, 
        container& destination)
    {
        namespace me = ::tools;

        //namespace me = ::tools::stringed;
        //drequired_compatible(s1, text, s2, pattern);

        static_assert(
            ::std::is_const<container>::value == 0,
            "'container' can not be 'const'"
        );
        return detail::match_pattern( 
            me::c_str(text), 
            me::length(text),
            me::c_str(pattern),
            me::length(pattern),
            destination
        );
    }

} // namespace tools


//=== optimize_mask: implementation ============================================
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

    // return new length
    template<class str> size_t optimize_mask(str& mask)
    {
        namespace me = ::tools::stringed;

        using x = ::std::remove_reference_t<str>;
        using z = ::std::remove_pointer_t<str>;

        static_assert(
            !::std::is_const<x>::value,
            "expected non-const object"
        );
        static_assert(
            !::std::is_const<z>::value,
            "expected non-const object"
        );

        const auto new_len = ::tools::optimize_mask(
            me::str(mask), 
            me::length(mask)
        );
        me::fixed_new_size(mask, new_len);
        return new_len;
    }

} // namespace tools
//==============================================================================
//==============================================================================
#endif // !dTOOLS_MATCH_PATTERN_USED_



