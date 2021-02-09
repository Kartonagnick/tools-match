
// [2021y-02m-05d] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_STRINGED_CONCEPT_USED_
#define dTOOLS_STRINGED_CONCEPT_USED_ 100
//==============================================================================
//==============================================================================
namespace tools 
{
    namespace stringed_v1
    {
        template<class t> struct noref      { using type = t; };
        template<class t> struct noref<t&>  { using type = t; };
        template<class t> struct noref<t&&> { using type = t; };
        template<class t> using noref_t = typename noref<t>::type;

        #define dSTRING_CONSEPT_(s) \
            decltype(::tools::stringed_v1::result_type<s>().c_str()) = nullptr

        template<class s> s result_type() noexcept;

        template<class s> noref_t<s> can_return_by_value(s& ) noexcept;
        template<class s> noref_t<s> can_return_by_value(s&&) noexcept;

        template<class s, dSTRING_CONSEPT_(s)> 
            void must_be_string(s&&) noexcept;

        template<class ch, size_t n> 
            void must_be_array(ch( &)[n]) noexcept;

        template<class ch, size_t n> 
            void must_be_array(ch(&&)[n]) noexcept;

        template<class t> void can_be_pointer(t*)                 noexcept;
        template<class t> void can_be_pointer(t* const)           noexcept;
        template<class t> void can_be_pointer(t* volatile)        noexcept;
        template<class t> void can_be_pointer(t* volatile const)  noexcept;

    } // namespace stringed_v1

    #define dPOINTER_OR_ARRAY_CONSEPT(ret, v)             \
        decltype((                                        \
            ::tools::stringed_v1::can_be_pointer(v),      \
            ::tools::stringed_v1::result_type<ret>()      \
        ))

    #define dSTRING_CONSEPT(ret, v)                       \
        decltype((                                        \
            ::tools::stringed_v1::must_be_string(v),      \
            ::tools::stringed_v1::result_type<ret>()      \
        ))

    #define dARRAY_CONSEPT(ret, v)                        \
        decltype((                                        \
            ::tools::stringed_v1::must_be_array(v),       \
            ::tools::stringed_v1::result_type<ret>()      \
        ))

    #define dPOINTER_CONSEPT(ret, v)                      \
        decltype((                                        \
            ::tools::stringed_v1::can_be_pointer(v),      \
            ::tools::stringed_v1::can_return_by_value(v), \
            ::tools::stringed_v1::result_type<ret>()      \
        ))

} // namespace tools 
//==============================================================================
//==============================================================================
#endif // !dTOOLS_STRINGED_CONCEPT_USED_
