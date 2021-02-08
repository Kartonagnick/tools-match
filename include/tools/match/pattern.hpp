
// [2021-02-05] Idrisov Denis R.
#pragma once

#ifndef dTOOLS_MATCH_PATTERN_USED_ 
#define dTOOLS_MATCH_PATTERN_USED_ 1

#include <tools/match/details.hpp>

//==============================================================================
//=== match_pattern ============================================================
namespace tools
{
    template<class s1, class s2>
    bool match_pattern(const s1& text, const s2& pattern) noexcept;

    template<class ch>
    bool match_pattern(const ch* s, const ch* p) noexcept;

    template<class s1, class s2, class container>
    bool match_pattern(const s1& text, const s2& pattern, container& dst);

} // namespace tools

//==============================================================================
//==============================================================================




//==============================================================================
//=== implementation ===========================================================
namespace tools
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

    template<class s1, class s2>
    bool match_pattern(const s1& text, const s2& pattern) noexcept
    {
        assert(::tools::valid_(text));
        assert(::tools::valid_(pattern));
        return ::tools::match_pattern(
            &text[0],
            &pattern[0]
        );
    }

} // namespace tools

//==============================================================================
//=== has_operator_access ======================================================

#define dDETAIL_CONSTANT(...) \
    ::std::integral_constant<bool, detail::__VA_ARGS__::value>

#ifndef dTOOLS_HAS_OPERATOR_ACCESS_USED_ 
#define dTOOLS_HAS_OPERATOR_ACCESS_USED_
namespace tools
{
    namespace detail
    {
        template<class container, class index>
        class has_operator_access
        {
            template <class cont, class idx> static 
            ::std::true_type check(
                ::std::add_pointer_t<
                    decltype(
                        ::std::declval<cont>()[::std::declval<idx>()]
                    )
                >
            );

            template <class, class> static ::std::false_type check(...);
        public:
            has_operator_access() = delete;
           ~has_operator_access() = delete;

            using type 
                = decltype(check<container, index>(nullptr));

            enum { value = type::value };
        };

    } // namespace detail

    template<class C, class I> 
    class has_operator_access
        : public dDETAIL_CONSTANT(has_operator_access<C, I>)
    {};

    #define dfor_has_operator_access(Cont, Val)              \
        ::std::enable_if_t<                                  \
            ::tools::has_operator_access<Cont, Val>::value   \
        >* = nullptr  
    
    #define dfor_hasnot_operator_access(Cont, Val)           \
        ::std::enable_if_t<                                  \
            ! ::tools::has_operator_access<Cont, Val>::value \
        >* = nullptr  

} // namespace tools
#endif // !dTOOLS_HAS_OPERATOR_ACCESS_USED_

//==============================================================================
//==============================================================================
#include <iterator>
namespace tools
{
    namespace match_detail
    {
        template<class ch>
        constexpr size_t offset(ch* const& last, ch* const& start) noexcept
        {
            assert(last);
            assert(start);
            assert(last >= start);
            return static_cast<size_t>(last - start);
        }

        #define dITERATOR \
            typename Cont::const_iterator

        // --- ::std::vector::operator[]
        // --- update iterator after realoc
        template<class Cont, class ch, 
            dfor_has_operator_access(Cont, size_t)
        >
        void add_symbol_(Cont& dst, const ch* const text, dITERATOR& iter)
        {
            assert(text);
            const auto index = ::std::distance(dst.cbegin(), iter);
            dst.emplace_back(text, 1); // add one symbol from 'text'
            iter = dst.cbegin() + index;
        }
      
        // --- ::std::list
        // --- does not need to be updated iterator
        template<class Cont, class ch, 
            dfor_hasnot_operator_access(Cont, size_t)
        >
        void add_symbol_(Cont& dst, const ch* const text, dITERATOR&)
        {
            assert(text);
            dst.emplace_back(text, 1); // add one symbol from 'text'
        }

        #undef dITERATOR

        template<class ch, class container>
        bool pattern(
            const ch*    text, 
            const size_t lentext, 
            const ch*    mask, 
            const size_t lenmask, 
            container&   dst) 
        {
            assert(text);
            assert(mask);

            namespace x = tools::match_detail;
            using str_type 
                = typename container::value_type;

            using char_t 
                = typename str_type::value_type;

            using iter_t 
                = typename container::const_iterator;

            static_assert(
                !::std::is_const<container>::value,
                "container can not be const"
            );

            static_assert(
                ::std::is_same<ch, char_t>::value,
                "symbols are not compatible"
            );
            assert(tools::length_(text) >= lentext);
            assert(tools::length_(mask) >= lenmask);

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
                const auto dist = x::offset(p, pst);
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
                    const size_t lenmask_ = x::offset(p, pst);
                    const auto success = lenmask_ == lenmask;
                    if(!success)
                        dst.clear();
                    return success;
                }

                bool next = false;
                if(*p == '?')
                {
                    if(!is_question)
                    {
                        is_question = true;
                        x::add_symbol_(dst, s, iter);
                    }
                    else
                    {
                        if(dst.empty())
                            x::add_symbol_(dst, s, iter);
                        else
                            dst.back() += *s;
                    }
                    next = true;
                }
                else if(*s == *p)
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
                    dst.emplace_back(::std::move(actual));

                    iter = dst.cend(); 
                    --iter;

                    s = ++rs;
                    p = rp;

                    assert(s >= st);
                    curlen = static_cast<size_t>(s - st);
                    continue;
                }
                else
                {
                    dst.clear();
                    return false;
                }
            }
        }

    } // namespace match_detail

    template<class s1, class s2, class container>
    bool match_pattern(
        const s1& text, 
        const s2& pattern, 
        container& destination)
    {
        static_assert(
            ::std::is_const<container>::value == 0,
            "'container' can not be 'const'"
        );
        assert(::tools::valid_(text));
        assert(::tools::valid_(pattern));
        return match_detail::pattern( 
            &text[0], 
            ::tools::length_(text),
            &pattern[0],
            ::tools::length_(pattern),
            destination
        );
    }

} // namespace tools

//==============================================================================
//==============================================================================
#endif // !dTOOLS_MATCH_PATTERN_USED_



