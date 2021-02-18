
// [2021y-02m-05d] Idrisov Denis R.
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
    const auto ok 
        = me::match_group("EURUSD", "+EURUSD, !EUR*");
    ASSERT_TRUE(ok);
}
TEST_COMPONENT(001)
{
    const auto ok 
        = me::match_group("EURUSD", "+EURUSD, !EUR*, *");
    ASSERT_TRUE(ok);
}
TEST_COMPONENT(002)
{
    const auto ok 
        = me::match_group("AUDCAD", "+EURUSD, !EUR*, *");
    ASSERT_TRUE(ok);
}
TEST_COMPONENT(003)
{
    const auto ok 
        = me::match_group("EURCAD", "+EURUSD, !EUR*, *");
    ASSERT_TRUE(!ok);
}

TEST_COMPONENT(004)
{
    const auto ok 
        = me::match_group("EURUSD", "!EUR*, +EURUSD");
    ASSERT_TRUE(!ok);
}

_TEST_COMPONENT(005)
{
    bool ok = false;
    ASSERT_DEATH_DEBUG(ok = me::match_group("EURUSD", "!+EURUSD"));
    (void)ok;
}


#endif // !TEST_TOOLS_MATCH_GROUP


