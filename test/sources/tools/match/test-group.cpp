
// [2021y-02m-05d] Idrisov Denis R.
#include <mygtest/test-list.hpp>

#ifdef TEST_TOOLS_MATCH_GROUP

#include <tools/match/group.hpp>

#define TEST_CASE_NAME tools
#define TEST_NUMBER(n) match_group_##n

namespace me = ::TEST_CASE_NAME;
//==============================================================================
namespace {} // namespace

//==============================================================================

#ifndef NDEBUG
// --- match_group(nullptr, mask)
TEST_COMPONENT(000)
{
    bool re = false;
    ASSERT_DEATH_DEBUG(
         char* mask = NULL;
         re = me::match_group("USOUSD", mask);
    );

    ASSERT_DEATH_DEBUG(
         wchar_t* mask = NULL;
         re = me::match_group(L"USOUSD", mask);
    );
	(void) re;
}

// --- match_group(mask, nullptr)
TEST_COMPONENT(001)
{
    bool re = false;
    ASSERT_DEATH_DEBUG(
        const char* const mask = NULL; 
        re = me::match_group("USOUSD", mask)
    );
    ASSERT_DEATH_DEBUG(
        const wchar_t* const mask = NULL; 
        re = me::match_group(L"USOUSD", mask)
    );
	(void) re;
}

// --- match_group(nullptr, nullptr)
TEST_COMPONENT(002)
{
    bool re = false;
    ASSERT_DEATH_DEBUG(
        const char* const text = NULL; 
        const char* const mask = NULL; 
        re = me::match_group(text, mask)
    );
    ASSERT_DEATH_DEBUG(
        const wchar_t* const text = NULL; 
        const wchar_t* const mask = NULL; 
        re = me::match_group(text, mask)
    );
    (void) re;	
}
#endif //!!NDEBUG

TEST_COMPONENT(003)
{
    const char* group 
        = "NASUSD,UKOUSD,USOUSD,Z30CHF,!*";
    ASSERT_TRUE(!me::match_group("USOUSD", group));
}
TEST_COMPONENT(004)
{
    const char* group 
        = "NASUSD, UKOUSD,USOUSD,Z30CHF,!*  ";
    ASSERT_TRUE(!me::match_group("USOUSD", group));
}
TEST_COMPONENT(005)
{
    const char* group 
        = " , NASUSD, UKOUSD,USOUSD,Z30CHF,!*  , ";
    ASSERT_TRUE(!me::match_group("USOUSD", group));
}
TEST_COMPONENT(006)
{
    const char* group 
        = " , ,NASUSD, UKOUSD,USOUSD,Z30CHF,!*  ,,";
    ASSERT_TRUE(!me::match_group("USOUSD", group));

}
TEST_COMPONENT(007)
{
    const char* group 
        = "NASUSD,UKOUSD,USOUSD,Z30CHF,*";
    ASSERT_TRUE(me::match_group("ASOUSD", group));
}
TEST_COMPONENT(008)
{
    const char* group 
        = "EUR*,!EURHHH";
    ASSERT_TRUE( me::match_group("EURUSD", group));
    ASSERT_TRUE( me::match_group("EURASD", group));
    ASSERT_TRUE(!me::match_group("EURHHH", group));
}
TEST_COMPONENT(009)
{
    const char* group 
        = ",!EURHHH, EUR*";
    ASSERT_TRUE( me::match_group("EURUSD", group));
    ASSERT_TRUE( me::match_group("EURASD", group));
    ASSERT_TRUE(!me::match_group("EURHHH", group));
}
TEST_COMPONENT(010)
{
    const char* group 
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
    const char* group = "*,!EUR*";
    ASSERT_TRUE(!me::match_group("EURUSD", group));
    ASSERT_TRUE( me::match_group("RURUSD", group));
}
TEST_COMPONENT(012)
{
    const char* group = "!EUR*,*";
    ASSERT_TRUE(!me::match_group("EURUSD", group));
    ASSERT_TRUE( me::match_group("RURUSD", group));
}
TEST_COMPONENT(013)
{
    const char* group 
        = "*,!BTC*,!USD*,!EUR*,!AUD*,!GBP*,!NZD*,!CHF*,!CAD*,!SGD*,!XAU*,!XAG*";
    ASSERT_TRUE(!me::match_group("USD", group));
    ASSERT_TRUE( me::match_group("MMM", group));
}
TEST_COMPONENT(014)
{
    const char* group 
        = "EURUSD,*,GBDUSD";
    ASSERT_TRUE(me::match_group("MMM", group));
}
TEST_COMPONENT(015)
{
    const char* group 
        = ",!demo*, *  ,";
    ASSERT_TRUE(me::match_group("dd-01", group));
}
TEST_COMPONENT(016)
{
    const char* group 
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

#ifndef NDEBUG
// --- invalid symbol
TEST_COMPONENT(024)
{
    bool re = false;

    // символ не имеет права начинаться с пробелов
    ASSERT_DEATH_DEBUG(re = me::match_group(" work", " work"));

    // символ не имеет права завершаться пробелами
    ASSERT_DEATH_DEBUG(re = me::match_group("work ", " work"));
	(void) re;
}
#endif

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

TEST_COMPONENT(027)
{
    const auto ok = me::match_group("cy-a", "sv-*, *-a-*, *-a, a-*");
    ASSERT_TRUE(ok);
}


#endif // !TEST_TOOLS_MATCH_GROUP


