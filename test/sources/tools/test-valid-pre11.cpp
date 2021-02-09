
// [2021y-02m-05d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================

#ifdef TEST_TOOLS_VALID

#define dTEST_COMPONENT tools
#define dTEST_METHOD valid
#define dTEST_TAG pre11

#include <tools/valid.hpp>
#include "test-staff.hpp"

#ifdef dHAS_RVALUE_ARRAY
    dMESSAGE("[test][until c++11] tools/valid.hpp: enabled -> dHAS_RVALUE_ARRAY")
#else
    dMESSAGE("[test][until c++11] tools/valid.hpp: disabled -> dHAS_RVALUE_ARRAY")
#endif

namespace me = ::tools;
using namespace staff;
//==============================================================================
//==============================================================================
namespace test_stringed_valid {}
namespace test = test_stringed_valid;

namespace test_stringed_valid
{
    template<class type> void array()
    {
        type arr[] = { '\0' };
        type (&ref)[1] = arr;
        ASSERT_TRUE(me::valid(arr));
        ASSERT_TRUE(me::valid(ref));
    }

	template<class str> void string()
    {
		typedef typename str::value_type ch;

        ch arr[2] = {};
        str txt   = arr;
        str& ref  = txt;

        ASSERT_TRUE(me::valid(txt ));
        ASSERT_TRUE(me::valid(ref ));
    }

    template<class ptr> void pointer()
    {
        ptr val  = 0;
        ptr& ref = val;
        ASSERT_TRUE(!me::valid(val ));
        ASSERT_TRUE(!me::valid(ref ));
    }

    template<class ch, class ptr, class arr> 
    void pointer(const arr& text)
    {
        enum { size = sizeof(text)/sizeof(text[0]) };
        ch initial[size];
        for (size_t i = 0; i != size; ++i)
            initial[i] = static_cast<ch>(text[i]);
        ASSERT_TRUE(initial[size - 1] == 0);

        ptr val  = initial;
        ptr& ref = val;
        ASSERT_TRUE(me::valid(val ));
        ASSERT_TRUE(me::valid(ref ));
    }

} // namespace test_stringed_valid

//..............................................................................

namespace test_stringed_valid
{
	template<class ch> void array_case()
	{
        test::array<ch>();
        test::array<const ch>();
		test::array<volatile ch>();
		test::array<volatile const ch>();
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
    
	template<class str> void string_case()
    {
        test::string<str_t>();
        test::string<const str_t>();
     // test::string<volatile str_t>(); <--- not support
    }

} // namespace test_stringed_valid

//==============================================================================
//==============================================================================

//--- array
TEST_COMPONENT(000)
{
	test::array_case<char>();
	test::array_case<wchar_t>();
}

//--- string
TEST_COMPONENT(001)
{
	test::string_case<str_t>();
	test::string_case<str_w>();
	test::string_case<str_i>();
}

//--- null pointer
TEST_COMPONENT(002)
{
    test::pointer_case<char>();
    test::pointer_case<wchar_t>();
}

//--- pointer
TEST_COMPONENT(003)
{
    test::pointer_case<char>("");
    test::pointer_case<wchar_t>("");
}

//==============================================================================
//==============================================================================
#endif // !TEST_TOOLS_VALID