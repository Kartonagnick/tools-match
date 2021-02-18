
// [2021y-02m-19d] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_MATCH_GROUP_PLUS

#include <tools/match/group.hpp>

#define dTEST_COMPONENT tools
#define dTEST_METHOD match_group
#define dTEST_TAG plus

namespace me = ::tools;
//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    const bool ok 
        = me::match_group("EURUSD", "+EURUSD, !EUR*");
    ASSERT_TRUE(ok);
}
TEST_COMPONENT(001)
{
    const bool ok 
        = me::match_group("EURUSD", "+EURUSD, !EUR*, *");
    ASSERT_TRUE(ok);
}
TEST_COMPONENT(002)
{
    const bool ok 
        = me::match_group("AUDCAD", "+EURUSD, !EUR*, *");
    ASSERT_TRUE(ok);
}
TEST_COMPONENT(003)
{
    const bool ok 
        = me::match_group("EURCAD", "+EURUSD, !EUR*, *");
    ASSERT_TRUE(!ok);
}
TEST_COMPONENT(004)
{
    const bool ok 
        = me::match_group("EURUSD", "!EUR*, +EURUSD");
    ASSERT_TRUE(!ok);
}
TEST_COMPONENT(005)
{
    const bool ok 
        = me::match_group("EURUSD", "!+EURUSD, *");
    ASSERT_TRUE(!ok);
}
TEST_COMPONENT(006)
{
    const bool ok 
        = me::match_group("EURUSD", "+!EURUSD, *");
    ASSERT_TRUE(!ok);
}


#endif // !TEST_TOOLS_MATCH_GROUP


