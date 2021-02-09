
// [2021y-02m-05d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================

#ifdef TEST_TOOLS_VALID

#include <tools/features.hpp>
#ifdef dHAS_CPP11

#define dTEST_COMPONENT tools
#define dTEST_METHOD valid
#define dTEST_TAG cpp11

#include <tools/valid.hpp>
#include "test-staff.hpp"

#ifdef dHAS_RVALUE_ARRAY
    dMESSAGE("[test][since c++11] tools/valid.hpp: enabled -> dHAS_RVALUE_ARRAY")
#else
    dMESSAGE("[test][since c++11] tools/valid.hpp: disabled -> dHAS_RVALUE_ARRAY")
#endif

namespace me = ::tools;
using namespace staff;
//==============================================================================
//==============================================================================
namespace test_stringed_valid {}
namespace test = test_stringed_valid;

namespace test_stringed_valid
{
    constexpr const char*    meow_a =  "meow";
    constexpr const wchar_t* meow_w = L"meow";

    constexpr const char*    null_a =  nullptr;
    constexpr const wchar_t* null_w =  nullptr;

    constexpr const std::nullptr_t cnil = nullptr;
    constexpr std::nullptr_t nil = nullptr;

    static_assert(me::valid(meow_a)             , "error(1): expected 'true'"  );
    static_assert(me::valid(meow_w)             , "error(2): expected 'true'"  );
    static_assert(me::valid(std::move(meow_a))  , "error(3): expected 'true'"  );
    static_assert(me::valid(std::move(meow_w))  , "error(4): expected 'true'"  );

    static_assert(!me::valid(null_a)            , "error(5): expected 'false'" );
    static_assert(!me::valid(null_w)            , "error(6): expected 'false'" );
    static_assert(!me::valid(nullptr)           , "error(7): expected 'false'" );
    static_assert(!me::valid(cnil)              , "error(8): expected 'false'" );
    static_assert(!me::valid(nil)               , "error(9): expected 'false'" );

    static_assert(!me::valid(std::move(null_a)) , "error(10): expected 'false'" );
    static_assert(!me::valid(std::move(null_w)) , "error(11): expected 'false'");
    static_assert(!me::valid(std::move(nullptr)), "error(12): expected 'false'");
    static_assert(!me::valid(std::move(cnil))   , "error(13): expected 'false'");
    static_assert(!me::valid(std::move(nil))    , "error(14): expected 'false'");

    static_assert(me::valid(  "meow")           , "error(15): expected 'true'" );
    static_assert(me::valid( L"meow")           , "error(16): expected 'true'" );
    static_assert(me::valid(u8"meow")           , "error(17): expected 'true'" );

    #ifdef dHAS_RVALUE_ARRAY
    static_assert(me::valid(std::move("meow"  )), "error(16): expected 'true'" );
    static_assert(me::valid(std::move(L"meow" )), "error(17): expected 'true'" );
    static_assert(me::valid(std::move(u8"meow")), "error(18): expected 'true'" );
    #endif

} // namespace test_stringed_valid

//..............................................................................

namespace test_stringed_valid
{
    template<class type> void array()
    {
        type arr[] = { '\0' };
        type (&ref)[1] = arr;
        ASSERT_TRUE(me::valid(arr));
        ASSERT_TRUE(me::valid(ref));
        #ifdef dHAS_RVALUE_ARRAY
            type (&&rval)[1] = std::move(ref);
            ASSERT_TRUE(me::valid(rval));
            ASSERT_TRUE(me::valid(std::move(arr )));
            ASSERT_TRUE(me::valid(std::move(ref )));
            ASSERT_TRUE(me::valid(std::move(rval)));
        #endif
    }
	
    template<class str> void string()
    {
        using ch = typename str::value_type;

        ch arr[2]  = {};
        str txt    = arr;
        str& ref   = txt;
        str&& rval = std::move(txt);

        ASSERT_TRUE(me::valid(txt ));
        ASSERT_TRUE(me::valid(ref ));
		ASSERT_TRUE(me::valid(rval));
		ASSERT_TRUE(me::valid(std::move(txt )));
		ASSERT_TRUE(me::valid(std::move(ref )));
		ASSERT_TRUE(me::valid(std::move(rval)));
    }

    template<class ptr> void pointer()
    {
        ptr val    = 0;
        ptr& ref   = val;
		ptr&& rval = std::move(ref);

        ASSERT_TRUE(!me::valid(val ));
        ASSERT_TRUE(!me::valid(ref ));
		ASSERT_TRUE(!me::valid(rval));
		ASSERT_TRUE(!me::valid(std::move(val )));
		ASSERT_TRUE(!me::valid(std::move(ref )));
		ASSERT_TRUE(!me::valid(std::move(rval)));
    }

    template<class ptr, class arr> 
    void pointer(const arr& text)
    {
        using ch = std::remove_cv_t<
            std::remove_pointer_t<ptr>
        >;

        enum { size = sizeof(text)/sizeof(text[0]) };
        ch initial[size];
        for (size_t i = 0; i != size; ++i)
            initial[i] = static_cast<ch>(text[i]);
        ASSERT_TRUE(initial[size - 1] == 0);

        ptr val    = initial;
        ptr& ref   = val;
        ptr&& rval = std::move(ref);
        ASSERT_TRUE(me::valid(val ));
        ASSERT_TRUE(me::valid(ref ));
        ASSERT_TRUE(me::valid(rval));
        ASSERT_TRUE(me::valid(std::move(val )));
        ASSERT_TRUE(me::valid(std::move(ref )));
        ASSERT_TRUE(me::valid(std::move(rval)));
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
        test::pointer<ch*>(text);
       
        test::pointer<ch* const>(text);
        test::pointer<ch* volatile>(text);
        test::pointer<ch* volatile const>(text);
       
        test::pointer<const ch*>(text);
        test::pointer<volatile ch*>(text);
        test::pointer<volatile const ch*>(text);
       
        test::pointer<const ch* const>(text);
        test::pointer<volatile ch* const >(text);
        test::pointer<volatile const ch* const >(text);
       
        test::pointer<const ch* volatile>(text);
        test::pointer<volatile ch* volatile >(text);
        test::pointer<volatile const ch* volatile >(text);
       
        test::pointer<const ch* volatile const>(text);
        test::pointer<volatile ch* volatile const>(text);
        test::pointer<volatile const ch* volatile const>(text);
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
#endif // !dHAS_CPP11
#endif // !TEST_TOOLS_VALID