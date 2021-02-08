
// [2021-02-05] Idrisov Denis R.
#pragma once

#ifndef dTOOLS_MATCH_PATTERN_CONT_USED_ 
#define dTOOLS_MATCH_PATTERN_CONT_USED_ 100

#include <tools/match/details.hpp>
#include <iterator>

//==============================================================================
//=== declaration ==============================================================
namespace tools
{
    template<class s1, class s2, class container>
    dNODISCARD bool match_pattern(
        const s1& text,
        const s2& mask, 
        container& dst
    );

} // namespace tools
//==============================================================================
//==============================================================================





//==============================================================================
//=== implementation ===========================================================
namespace tools
{
    namespace detail_pattern
    {
        template<class ch>  
        size_t offset(const ch* const last, const ch* const start) 
        {
            dASSERT(last >= start);
            return static_cast<size_t>(last - start);
        }

        template<class container>
        class has_operator_asccess
        {
            typedef char (&no )[1]; 
            typedef char (&yes)[2];

            typedef container x;
            typedef typename x::value_type 
                elem;

            typedef const elem& (x::* sig)(const size_t) const;

            template<class, sig> struct help {}; // <-- must be complete (bug with msvc2013)

            #if 0   
            bug with msvc2013:

            c:\program files (x86)\microsoft visual studio 12.0\vc\include\xmemory0(572): 
            fatal error C1001: An internal error has occurred in the compiler.
            2>  (compiler file 'msc1.cpp', line 1325)
            #endif

            template<class> static no check(...);

            template<class u> static 
                yes check(help< u, &u::operator[] >* p);

            enum { result = sizeof(check<x>(0)) };
        public:
            has_operator_asccess(){};
            enum { value = result != sizeof(no) };
        };

        #ifdef dHAS_CPP17
        template<class container> 
        class has_operator_asccess_noexcept
        {
            typedef char (&no )[1]; 
            typedef char (&yes)[2];

            typedef container x;
            typedef typename x::value_type 
                elem;

            typedef const elem& (x::* sig)(const size_t) const noexcept;

            template<class, sig> struct help; 

            template<class> static no check(...);
            template<class u> static 
                yes check(help<u, &u::operator[] >* p);

            enum { result = sizeof(check<x>(0)) };
        public:
            has_operator_asccess_noexcept() = delete;
            enum { value = result != sizeof(no) };
        };
        #endif // !dHAS_CPP17

        #ifdef dHAS_CPP17

            #define dIS_VECTOR_                                  \
                has_operator_asccess<container>::value ||        \
                has_operator_asccess_noexcept<container>::value  \

        #else

            #define dIS_VECTOR_ \
                has_operator_asccess<container>::value

        #endif // dHAS_CPP17

        template<class container, bool = dIS_VECTOR_>
            struct agent;

        #undef dIS_VECTOR_

        template<class cont> struct agent <cont, true>
        {
            typedef typename cont::value_type
                str_type;
            typedef typename str_type::value_type
                ch;
            typedef typename cont::const_iterator
                iter_t;
            typedef ::std::iterator_traits<iter_t>
                traits_t;
            typedef typename traits_t::difference_type
                diff_t;

            static void update(cont& dst, const ch* const text, iter_t& iter)
            {
                dASSERT(text);
                const iter_t beg = dst.begin();

                const diff_t v = ::std::distance(beg, iter);
                dASSERT(v >= 0);

                #ifdef dHAS_CPP11
                    dst.emplace_back(text, 1);
                #else
                    const str_type el;
                    dst.push_back(el);
                    str_type& ref = dst.back();
                    ref += *text;
                #endif
                iter = dst.begin() + v;
            }
        };

        template<class cont> struct agent <cont, false>
        {
            typedef typename cont::value_type
                str_type;
            typedef typename str_type::value_type
                ch;
            typedef typename cont::const_iterator
                iter_t;

            static void update(cont& dst, const ch* const text, iter_t&)
            {
                dASSERT(text);
                #ifdef dHAS_CPP11
                    dst.emplace_back(text, 1);
                #else
                    const str_type el;
                    dst.push_back(el);
                    str_type& ref = dst.back();
                    ref += text[0];
                #endif
            }
        };

        template<class ch, class container>
        bool match_pattern(
            const ch*    text, 
            const size_t lentext, 
            const ch*    mask, 
            const size_t lenmask, 
            container&   dst) 
        {
            typedef typename container::value_type
                str_type;
            typedef typename container::const_iterator
                iter_t;
            namespace me = ::tools::detail_pattern;
            typedef me::agent<container>                                
                agent_t;

            #ifdef dHAS_CPP11
            typedef typename str_type::value_type
                char_t;
            
            static_assert(
                !::std::is_const<container>::value,
                "'container' can not be const"
            );
            static_assert(
                ::std::is_same<ch, char_t>::value,
                "'symbols' are not compatible"
            );
            #endif

            dASSERT(text);
            dASSERT(mask);
            dASSERT(::tools::strlength(text) >= lentext);
            dASSERT(::tools::strlength(mask) >= lenmask);

            #ifdef dHAS_CPP11
                constexpr const ch null =  0;
                constexpr const ch star = '*';
                constexpr const ch qust = '?';
            #else
                const ch null =  0;
                const ch star = '*';
                const ch qust = '?';
            #endif

            if(*text == null && *mask == null)
                return true;

            const ch* st  = text;
            const ch* s   = text;
            const ch* pst = mask;
            const ch* p   = mask;

            const ch* rs  = NULL;
            const ch* rp  = NULL;

            dst.clear();

            iter_t iter = dst.end();
            
            size_t curlen = 0;
            bool is_question = false;
            bool is_star     = false;

            for(;;)
            {
                const size_t dist = me::offset(p, pst);
                dASSERT(p && dist <= lenmask);
                if(dist < lenmask  && *p == star)
                {
                    rs = s;
                    rp = ++p;
                    if(!is_star)
                    {
                        #ifdef dHAS_CPP11
                            dst.emplace_back();
                        #else
                            const str_type empty;
                            dst.push_back(empty);
                        #endif

                        iter = dst.end();
                        --iter;
                    }
                    is_star = true;                    
                    continue;
                }

                is_star = false;

                if(lentext == curlen)
                {
                    const bool success
                        = lenmask == me::offset(p, pst);
                    if(!success)
                        dst.clear();
                    return success;
                }

                bool next = false;
                if(*p == qust)
                {
                    if(!is_question)
                    {
                        is_question = true;
                        agent_t::update(dst, s, iter);
                    }
                    else
                    {
                        if(dst.empty())
                            agent_t::update(dst, s, iter);
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
                    ++s; ++p; ++curlen;
                    continue;
                }
           
                if(rs)
                {
                    dASSERT(!dst.empty());
                    is_question = false;
                    str_type actual = *iter;
                    actual += *rs;
                    dst.erase(iter, dst.end());

                    #ifdef dHAS_CPP11
                        dst.emplace_back(::std::move(actual));
                    #else
                        dst.push_back(actual);
                    #endif

                    iter = dst.end(); 
                    --iter;

                    s = ++rs;
                    p = rp;

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

    } // namespace detail_pattern

    template<class s1, class s2, class container>
    dNODISCARD bool match_pattern(const s1& text, const s2& mask, container& destination)
    {
        #ifdef dHAS_CPP11
        static_assert(::std::is_const<container>::value == 0,
            "'container' can not be 'const'"
        );
        #endif

        dASSERT(::tools::valid(text));
        dASSERT(::tools::valid(mask));
        const size_t len_text = ::tools::strlength(text);
        const size_t len_mask = ::tools::strlength(mask);
        return detail_pattern::match_pattern( 
            &text[0], len_text,
            &mask[0], len_mask,
            destination
        );
    }

} // namespace tools

//==============================================================================
//==============================================================================
#endif // !dTOOLS_MATCH_PATTERN_CONT_USED_



