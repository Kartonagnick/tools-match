
// [2021y-02m-19d] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_MATCH_GROUP_EXTRA

#include <tools/match/group.hpp>

#define dTEST_COMPONENT tools
#define dTEST_METHOD match_group
#define dTEST_TAG extra

namespace me = ::tools;
//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    const bool ok 
        = me::match_group("EURUSD", "FOREX", "FOREX, !AUD*");
    ASSERT_TRUE(ok);
}
TEST_COMPONENT(001)
{
    const bool ok 
        = me::match_group("EURUSD", "FOREX", "EURUSD, !AUD*");
    ASSERT_TRUE(ok);
}
TEST_COMPONENT(002)
{
    const bool ok 
        = me::match_group("AUDCAD", "FOREX", "FOREX, !EUR*, *");
    ASSERT_TRUE(ok);
}
TEST_COMPONENT(003)
{
    const bool ok 
        = me::match_group("EURUSD", "FOREX", "FOREX, !EUR*, *");
    ASSERT_TRUE(!ok);
}
TEST_COMPONENT(004)
{
    const bool ok 
        = me::match_group("EURUSD", "FOREX", "!EUR*, FOREX, *");
    ASSERT_TRUE(!ok);
}
TEST_COMPONENT(005)
{
    const bool ok 
        = me::match_group("EURCAD", "FOREX", "!*USD, FOREX");
    ASSERT_TRUE(ok);
}
TEST_COMPONENT(006)
{
    const bool ok 
        = me::match_group("EURUSD", "FOREX", "+EURUSD, !FOREX, *");
    ASSERT_TRUE(ok);
}
TEST_COMPONENT(007)
{
    const bool ok 
        = me::match_group("EURUSD", "FOREX", "FOREX, !EURUSD");
    ASSERT_TRUE(!ok);
}
TEST_COMPONENT(008)
{
    const bool ok 
        = me::match_group("EURUSD", "FOREX", "FOREX, +!EURUSD, *");
    ASSERT_TRUE(!ok);
}

#ifndef NDEBUG
TEST_COMPONENT(009)
{
    bool ok = false;
    const char* nil = 0;
    ASSERT_DEATH_DEBUG(ok = me::match_group(nil, "" , "" ));
    ASSERT_DEATH_DEBUG(ok = me::match_group(nil, nil, "" ));
    ASSERT_DEATH_DEBUG(ok = me::match_group(nil, nil, nil));
    ASSERT_DEATH_DEBUG(ok = me::match_group("" , "" , nil));
    ASSERT_DEATH_DEBUG(ok = me::match_group("" , nil, nil));
    ASSERT_DEATH_DEBUG(ok = me::match_group("" , nil, "" ));
    ASSERT_DEATH_DEBUG(ok = me::match_group(nil, "" , nil));
    (void)ok;
}
#endif

#endif // !TEST_TOOLS_MATCH_GROUP_EXTRA


