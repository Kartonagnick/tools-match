
// [2021-02-05] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_STRINGED_CONCEPT

#include <tools/features.hpp>
#ifdef dHAS_CPP11

#define dTEST_COMPONENT tools, stringed
#define dTEST_METHOD concept
#define dTEST_TAG tdd

#include <tools/stringed/concept.hpp>
#include "test-staff.hpp"

#ifdef dHAS_RVALUE_ARRAY
    dMESSAGE("[test] tools/stringed/concept: enabled -> dHAS_RVALUE_ARRAY")
#else
    dMESSAGE("[test] tools/stringed/concept: disabled -> dHAS_RVALUE_ARRAY")
#endif
dMESSAGE("[test] tools/stringed/concept: volatile std::string -> not support")

using namespace staff;
//==============================================================================
//==============================================================================

namespace test_stringed_concept
{
    namespace test = test_stringed_concept;

    enum eCATEGORY
    {
        eARRAY, ePOINTER, eSTRING
    };

    template<class s>
    constexpr auto check(s&& v) -> dARRAY_CONSEPT(eCATEGORY, v)
        { return eCATEGORY::eARRAY; }

    template<class s>
    constexpr auto check(s&& v) -> dPOINTER_CONSEPT(eCATEGORY, v)
        { return eCATEGORY::ePOINTER; }

    template<class s>
    constexpr auto check(s&& v) -> dSTRING_CONSEPT(eCATEGORY, v)
        { return eCATEGORY::eSTRING; }

    template<class type> void array()
    {
        type arr[] = { '\0' };
        type (&ref)[1] = arr;
        ASSERT_TRUE(test::check(arr) == eCATEGORY::eARRAY);
        ASSERT_TRUE(test::check(ref) == eCATEGORY::eARRAY);
        #ifdef dHAS_RVALUE_ARRAY
            type (&&rval)[1] = std::move(ref);
            ASSERT_TRUE(test::check(rval) == eCATEGORY::eARRAY);
            ASSERT_TRUE(test::check(arr ) == eCATEGORY::eARRAY);
            ASSERT_TRUE(test::check(ref ) == eCATEGORY::eARRAY);
            ASSERT_TRUE(test::check(rval) == eCATEGORY::eARRAY);
        #endif
    }

    template<class str> void string()
    {
        using ch = typename str::value_type;

        ch arr[2]  = {};
        str txt    = arr;
        str& ref   = txt;
        str&& rval = std::move(txt);

        ASSERT_TRUE(test::check(txt ) == eCATEGORY::eSTRING);
        ASSERT_TRUE(test::check(ref ) == eCATEGORY::eSTRING);
        ASSERT_TRUE(test::check(rval) == eCATEGORY::eSTRING);
            
        ASSERT_TRUE(test::check(std::move(txt )) == eCATEGORY::eSTRING);
        ASSERT_TRUE(test::check(std::move(ref )) == eCATEGORY::eSTRING);
        ASSERT_TRUE(test::check(std::move(rval)) == eCATEGORY::eSTRING);
    }

    template<class ptr> void pointer()
    {
        using ch = std::remove_cv_t<
            std::remove_reference_t<
                std::remove_pointer_t<ptr>
            >
        >;

        ch arr[2]  = {};
        ptr val    = arr;
        ptr& ref   = val;
        ptr&& rval = std::move(ref);
        ASSERT_TRUE(test::check(val ) == eCATEGORY::ePOINTER);
        ASSERT_TRUE(test::check(ref ) == eCATEGORY::ePOINTER);
        ASSERT_TRUE(test::check(rval) == eCATEGORY::ePOINTER);
        ASSERT_TRUE(test::check(std::move(val )) == eCATEGORY::ePOINTER);
        ASSERT_TRUE(test::check(std::move(ref )) == eCATEGORY::ePOINTER);
        ASSERT_TRUE(test::check(std::move(rval)) == eCATEGORY::ePOINTER);
    }

    template<class ch> void test_pointer()
    {
        test::pointer<ch*>();
       
        test::pointer<ch* const>();
        test::pointer<ch* volatile>();
        test::pointer<ch* volatile const>();
       
        test::pointer<const ch*>();
        test::pointer<volatile ch*>();
        test::pointer<volatile const ch*>();
       
        test::pointer<const ch* const>();
        test::pointer<volatile ch* const >();
        test::pointer<volatile const ch* const >();
       
        test::pointer<const ch* volatile>();
        test::pointer<volatile ch* volatile >();
        test::pointer<volatile const ch* volatile >();
       
        test::pointer<const ch* volatile const>();
        test::pointer<volatile ch* volatile const>();
        test::pointer<volatile const ch* volatile const>();
    }

} // namespace test_stringed_concept
using namespace test_stringed_concept;

//==============================================================================
//==============================================================================

//--- array
TEST_COMPONENT(000)
{
    test::array<char>();
    test::array<const char>();
    test::array<volatile char>();

    test::array<wchar_t>();
    test::array<const wchar_t>();
    test::array<volatile wchar_t>();
}

//--- string
TEST_COMPONENT(001)
{
    test::string<str_t>();
    test::string<const str_t>();
 // test::string<volatile str_t>(); <--- not support
}
TEST_COMPONENT(002)
{
    test::string<str_w>();
    test::string<const str_w>();
 // test::string<volatile str_w>(); <--- not support
}
TEST_COMPONENT(003)
{
    test::string<str_i>();
    test::string<const str_i>();
 // test::string<volatile str_i>(); <--- not support
}

//--- pointer
TEST_COMPONENT(004)
{
    test_pointer<char>();
    test_pointer<wchar_t>();
}

//==============================================================================
//==============================================================================
#endif // !dHAS_CPP11
#endif // !TEST_TOOLS_STRINGED_CONCEPT