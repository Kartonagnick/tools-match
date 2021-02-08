
// [2021-02-08] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================

#ifdef TEST_TOOLS_STRLENGTH

#define dTEST_COMPONENT tools
#define dTEST_METHOD strlength
#define dTEST_TAG pre11

#include <tools/strlength.hpp>
#include "test-staff.hpp"

#ifdef dHAS_RVALUE_ARRAY
    dMESSAGE("[test][until c++11] tools/strlength.hpp: enabled -> dHAS_RVALUE_ARRAY")
#else
    dMESSAGE("[test][until c++11] tools/strlength.hpp: disabled -> dHAS_RVALUE_ARRAY")
#endif
dMESSAGE("[test][until c++11] tools/strlength.hpp: volatile std::string -> not support")

namespace me = ::tools;
using namespace staff;
//==============================================================================
//==============================================================================
namespace test_stringed_strlength {}
namespace test = test_stringed_strlength;

//..............................................................................

namespace test_stringed_strlength
{
    template<class type> void array()
    {
        type arr[] = { '\0' };
        type (&ref)[1] = arr;
        ASSERT_TRUE(me::strlength(arr) == 0);
        ASSERT_TRUE(me::strlength(ref) == 0);
    }
	
    template<class str> void string()
    {
        typedef typename str::value_type ch;
        ch arr[2]  = {};
        str txt    = arr;
        str& ref   = txt;
        ASSERT_TRUE(me::strlength(txt) == 0);
        ASSERT_TRUE(me::strlength(ref) == 0);
    }

    template<class ptr> void pointer()
    {
        ptr val    = 0;
        ptr& ref   = val;
        size_t len = 0;
        ASSERT_DEATH_DEBUG(len = me::strlength(val));
        ASSERT_DEATH_DEBUG(len = me::strlength(ref));
    }

    #define dINITIALIZE(initial)                        \
        enum { size = sizeof(text) / sizeof(text[0]) }; \
        enum { len = size - 1 };                        \
        ch initial[size];                               \
        for (size_t i = 0; i != size; ++i)              \
            initial[i] = static_cast<ch>(text[i]);      \
        ASSERT_TRUE(initial[len] == 0)

    #define dINIT_PTR(initial)                          \
        dINITIALIZE(initial)

    template<class ch, class type, class str> void array(const str& text)
    {
        dINITIALIZE(arr);
        type (&ref)[size] = arr;
        ASSERT_TRUE(me::strlength(arr) == len);
        ASSERT_TRUE(me::strlength(ref) == len);
    }

    template<class str, class arr> void string(const arr& text)
    {
        typedef typename str::value_type ch;
        dINITIALIZE(initial);
        str txt    = initial;
        str& ref   = txt;

        ASSERT_TRUE(me::strlength(txt) == len);
        ASSERT_TRUE(me::strlength(ref) == len);
    }

    template<class ch, class ptr, class str> 
    void pointer(const str& text)
    {
        dINITIALIZE(initial);
        ptr val    = initial;
        ptr& ref   = val;
        ASSERT_TRUE(me::strlength(val) == len);
        ASSERT_TRUE(me::strlength(ref) == len);
    }

} // namespace test_stringed_strlength

//..............................................................................

namespace test_stringed_strlength
{
	template<class ch> void array_case()
	{
        test::array<ch>();
        test::array<const ch>();
		test::array<volatile ch>();
		test::array<volatile const ch>();
	}

	template<class str> void string_case()
    {
        test::string<str_t>();
        test::string<const str_t>();
     // test::string<volatile str_t>(); <--- not support
    }

    template<class ch> void pointer_case()
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

}// namespace test_stringed_strlength

//..............................................................................

namespace test_stringed_strlength
{

    template<class ch, class arr>
    void array_case(const arr& text)
	{
        test::array<ch, ch>(text);
        test::array<ch, const ch>(text);
		test::array<ch, volatile ch>(text);
		test::array<ch, volatile const ch>(text);
	}

    template<class ch, class arr>
    void string_case(const arr& text)
	{
        test::string<str_t>(text);
        test::string<const str_t>(text);
     // test::string<volatile str_t>(); <--- not support
	}

	template<class ch, class arr>
    void pointer_case(const arr& text)
    {
        test::pointer<ch, ch*>(text);
       
        test::pointer<ch, ch* const>(text);
        test::pointer<ch, ch* volatile>(text);
        test::pointer<ch, ch* volatile const>(text);
       
        test::pointer<ch, const ch*>(text);
        test::pointer<ch, volatile ch*>(text);
        test::pointer<ch, volatile const ch*>(text);
       
        test::pointer<ch, const ch* const>(text);
        test::pointer<ch, volatile ch* const >(text);
        test::pointer<ch, volatile const ch* const >(text);
       
        test::pointer<ch, const ch* volatile>(text);
        test::pointer<ch, volatile ch* volatile >(text);
        test::pointer<ch, volatile const ch* volatile >(text);
       
        test::pointer<ch, const ch* volatile const>(text);
        test::pointer<ch, volatile ch* volatile const>(text);
        test::pointer<ch, volatile const ch* volatile const>(text);
    }

} // namespace test_stringed_strlength

//==============================================================================
//==============================================================================

//--- array
TEST_COMPONENT(000)
{
	test::array_case<char>();
	test::array_case<wchar_t>();

	test::array_case<char>("");
	test::array_case<wchar_t>("");
}

TEST_COMPONENT(001)
{
	test::array_case<char>("12");
	test::array_case<wchar_t>("12");
}

//--- string
TEST_COMPONENT(002)
{
	test::string_case<str_t>();
	test::string_case<str_w>();
	test::string_case<str_i>();

	test::string_case<str_t>("");
	test::string_case<str_w>("");
	test::string_case<str_i>("");
}
TEST_COMPONENT(003)
{
	test::string_case<str_t>("12");
	test::string_case<str_w>("12");
	test::string_case<str_i>("12");
}

//--- null pointer
#ifndef NDEBUG
TEST_COMPONENT(004)
{
    test::pointer_case<char>();
    test::pointer_case<wchar_t>();
}
#endif

//--- pointer
TEST_COMPONENT(005)
{
    test::pointer_case<char>("");
    test::pointer_case<wchar_t>("");

    test::pointer_case<char>("12");
    test::pointer_case<wchar_t>("12");
}

//==============================================================================
//==============================================================================
#endif // !TEST_TOOLS_STRLENGTH