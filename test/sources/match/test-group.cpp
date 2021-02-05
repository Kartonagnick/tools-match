
#include <mygtest/test_list.hpp>

#ifdef TEST_TOOLS_MATCH_GROUP

#include <tools/match/group.hpp>

#define TEST_CASE_NAME tools
#define TEST_NUMBER(n) match_group_##n

namespace me = ::TEST_CASE_NAME;
//==============================================================================
namespace {} // namespace

//==============================================================================
// --- match_group(nullptr, mask)
TEST_COMPONENT(000)
{
    ASSERT_DEATH_DEBUG(
         char* mask = nullptr;
         me::match_group("USOUSD", mask);
    );

    ASSERT_DEATH_DEBUG(
         wchar_t* mask = nullptr;
         me::match_group(L"USOUSD", mask);
    );
}

// --- match_group(mask, nullptr)
TEST_COMPONENT(001)
{
    ASSERT_DEATH_DEBUG(
        const char* const mask = nullptr; 
        me::match_group("USOUSD", mask)
    );
    ASSERT_DEATH_DEBUG(
        const wchar_t* const mask = nullptr; 
        me::match_group(L"USOUSD", mask)
    );
}

// --- match_group(nullptr, nullptr)
TEST_COMPONENT(002)
{
    ASSERT_DEATH_DEBUG(
        const char* const text = nullptr; 
        const char* const mask = nullptr; 
        me::match_group(text, mask)
    );
    ASSERT_DEATH_DEBUG(
        const wchar_t* const text = nullptr; 
        const wchar_t* const mask = nullptr; 
        me::match_group(text, mask)
    );
}

TEST_COMPONENT(003)
{
    const auto* group 
        = "NASUSD,UKOUSD,USOUSD,Z30CHF,!*";
    ASSERT_TRUE(!me::match_group("USOUSD", group));
}
TEST_COMPONENT(004)
{
    const auto* group 
        = "NASUSD, UKOUSD,USOUSD,Z30CHF,!*  ";
    ASSERT_TRUE(!me::match_group("USOUSD", group));
}
TEST_COMPONENT(005)
{
    const auto* group 
        = " , NASUSD, UKOUSD,USOUSD,Z30CHF,!*  , ";
    ASSERT_TRUE(!me::match_group("USOUSD", group));
}
TEST_COMPONENT(006)
{
    const auto* group 
        = " , ,NASUSD, UKOUSD,USOUSD,Z30CHF,!*  ,,";
    ASSERT_TRUE(!me::match_group("USOUSD", group));

}
TEST_COMPONENT(007)
{
    const auto* group 
        = "NASUSD,UKOUSD,USOUSD,Z30CHF,*";
    ASSERT_TRUE(me::match_group("ASOUSD", group));
}
TEST_COMPONENT(008)
{
    const auto* group 
        = "EUR*,!EURHHH";
    ASSERT_TRUE( me::match_group("EURUSD", group));
    ASSERT_TRUE( me::match_group("EURASD", group));
    ASSERT_TRUE(!me::match_group("EURHHH", group));
}
TEST_COMPONENT(009)
{
    const auto* group 
        = ",!EURHHH, EUR*";
    ASSERT_TRUE( me::match_group("EURUSD", group));
    ASSERT_TRUE( me::match_group("EURASD", group));
    ASSERT_TRUE(!me::match_group("EURHHH", group));
}
TEST_COMPONENT(010)
{
    const auto* group 
        = "EUR*,!EUR*NH";
    ASSERT_TRUE( me::match_group("EURUSD", group));
    ASSERT_TRUE( me::match_group("EURASD", group));
    ASSERT_TRUE( me::match_group("EURHHH", group));
    ASSERT_TRUE(!me::match_group("EURNNH", group));
    ASSERT_TRUE(!me::match_group("EURNH" , group));
}
TEST_COMPONENT(011)
{
    //"*,!BTC*,!USD*,!EUR*,!AUD*,!GBP*,!NZD*,!CHF*,!CAD*,!SGD*,!XAU*,!XAG*",
    const auto* group = "*,!EUR*";
    ASSERT_TRUE(!me::match_group("EURUSD", group));
    ASSERT_TRUE( me::match_group("RURUSD", group));
}
TEST_COMPONENT(012)
{
    const auto* group = "!EUR*,*";
    ASSERT_TRUE(!me::match_group("EURUSD", group));
    ASSERT_TRUE( me::match_group("RURUSD", group));
}
TEST_COMPONENT(013)
{
    const auto* group 
        = "*,!BTC*,!USD*,!EUR*,!AUD*,!GBP*,!NZD*,!CHF*,!CAD*,!SGD*,!XAU*,!XAG*";
    ASSERT_TRUE(!me::match_group("USD", group));
    ASSERT_TRUE( me::match_group("MMM", group));
}
TEST_COMPONENT(014)
{
    const auto* group 
        = "EURUSD,*,GBDUSD";
    ASSERT_TRUE(me::match_group("MMM", group));
}
TEST_COMPONENT(015)
{
    const auto* group 
        = ",!demo*, *  ,";
    ASSERT_TRUE(me::match_group("dd-01", group));
}
TEST_COMPONENT(016)
{
    const auto* group 
        = ",!demo*, 111 222 ,";
    ASSERT_TRUE(me::match_group("111 222", group));
}
TEST_COMPONENT(017)
{
    const char value[] = "FL";
    const char group[] = ",FL,";
    ASSERT_TRUE(me::match_group(value, group));
}
TEST_COMPONENT(018)
{
    ASSERT_TRUE(me::match_group("FL", "*"));
    ASSERT_TRUE(me::match_group("CFD", "*"));
}
TEST_COMPONENT(019)
{
    ASSERT_TRUE(me::match_group("FL", ",*,"));
    ASSERT_TRUE(me::match_group("CFD", ",*,"));
}
TEST_COMPONENT(020)
{
    ASSERT_TRUE(!me::match_group("work"  , "* work"));
    ASSERT_TRUE( me::match_group("w work", "* work"));
    ASSERT_TRUE(!me::match_group("w work", " work" ));
}
TEST_COMPONENT(021)
{
    ASSERT_TRUE( me::match_group("work group"  , "work group"));
    ASSERT_TRUE(!me::match_group("work qroup"  , "work group"));
}
TEST_COMPONENT(022)
{
    ASSERT_TRUE(me::match_group("work" , " work"));
}
TEST_COMPONENT(023)
{
    ASSERT_TRUE(me::match_group("Forex"         , ",Forex*,CFD*,"));
    ASSERT_TRUE(me::match_group("ForexExt"      , ",Forex*,CFD*,"));
    ASSERT_TRUE(me::match_group("CFD on Metals" , ",Forex*,CFD*,"));
    ASSERT_TRUE(me::match_group("CFD US Stocks" , ",Forex*,CFD*,"));

    ASSERT_TRUE(me::match_group("Forex"         , "Forex*, CFD*"));
    ASSERT_TRUE(me::match_group("ForexExt"      , "Forex*, CFD*"));
    ASSERT_TRUE(me::match_group("CFD on Metals" , "Forex*, CFD*"));
    ASSERT_TRUE(me::match_group("CFD US Stocks" , "Forex*, CFD*"));
}

// --- invalid symbol
TEST_COMPONENT(024)
{
    // символ не имеет права начинаться с пробелов
    ASSERT_DEATH_DEBUG(me::match_group(" work", " work"));

    // символ не имеет права завершаться пробелами
    ASSERT_DEATH_DEBUG(me::match_group("work ", " work"));
}

// mask is empty
TEST_COMPONENT(025)
{
    ASSERT_TRUE(!me::match_group("Forex", ""));
    ASSERT_TRUE(me::match_group("", ""));
}

// group is empty
TEST_COMPONENT(026)
{
    ASSERT_TRUE(!me::match_group("", "Forex"));
}

#endif // !TEST_TOOLS_MATCH_GROUP


