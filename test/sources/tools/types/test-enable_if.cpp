
// [2021y-02m-09d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================

#ifdef TEST_TOOLS_ENABLE_IF

#define dTEST_COMPONENT tools, types
#define dTEST_METHOD enable_if
#define dTEST_TAG tdd

#include <tools/types/enable_if.hpp>
namespace me = ::tools;
//==============================================================================
//==============================================================================

namespace test_enable_if
{
    template<class t, class u> struct is_same
    {
        enum { value = false }; 
    };

    template<class t> struct is_same<t, t>
    { 
        enum { value = true  };
    };

    template<class t> struct check
    {
        enum { val = is_same<t, int>::value };
        typedef typename me::enable_if<val, char>::type
             type;
    };

    #define dENABLE_FOR(t) \
        typename me::enable_if< is_same<t, int>::value, bool >::type

    #define dDISABLE_FOR(t) \
        typename me::enable_if< !is_same<t, int>::value, bool >::type 

    template<class t>  dENABLE_FOR(t)  case_1(t) { return true ; }
    template<class t>  dDISABLE_FOR(t) case_1(t) { return false; }

    #undef dDISABLE_FOR
    #undef dENABLE_FOR

    #ifdef dHAS_TEMPLATE_FUNCTION_DEFAULT_PARAM
        #define dENABLE_FOR(t) \
            typename me::enable_if< is_same<t, int>::value >::type* = nullptr

        #define dDISABLE_FOR(t) \
            typename me::enable_if< !is_same<t, int>::value >::type* = nullptr

        template<class t, dENABLE_FOR(t) > bool case_2(t) { return true ; }
        template<class t, dDISABLE_FOR(t)> bool case_2(t) { return false; }

        #undef dDISABLE_FOR
        #undef dENABLE_FOR
    #endif

    #ifdef dHAS_USING_ALIAS

        #define dENABLE_FOR(t) \
            me::enable_if_t< is_same<t, int>::value >* = nullptr

        #define dDISABLE_FOR(t) \
            me::enable_if_t< !is_same<t, int>::value >* = nullptr

        template<class t, dENABLE_FOR(t) > bool case_3(t) { return true ; }
        template<class t, dDISABLE_FOR(t)> bool case_3(t) { return false; }
    #endif

} // namespace test_enable_if
using namespace test_enable_if;

//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    const bool ok = is_same<check<int>::type, char>::value;
    ASSERT_TRUE(ok);
}
TEST_COMPONENT(001)
{
    ASSERT_TRUE( case_1( 1 ));
    ASSERT_TRUE(!case_1('a'));
}

#ifdef dHAS_TEMPLATE_FUNCTION_DEFAULT_PARAM
TEST_COMPONENT(002)
{
    ASSERT_TRUE( case_2( 1 ));
    ASSERT_TRUE(!case_2('a'));
}
#endif

#ifdef dHAS_USING_ALIAS
TEST_COMPONENT(003)
{
    ASSERT_TRUE( case_3( 1 ));
    ASSERT_TRUE(!case_3('a'));
}
#endif

//==============================================================================
//==============================================================================

#endif // !TEST_TOOLS_ENABLE_IF
