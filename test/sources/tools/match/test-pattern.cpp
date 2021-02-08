
// [2021-02-05] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_MATCH_PATTERN

#include <tools/match/pattern.hpp>
#define dTEST_COMPONENT tools, match
#define dTEST_METHOD match_pattern
#define dTEST_TAG tdd

namespace me = ::tools;
//================================================================================
namespace
{
    const char* bool2string(const bool value) dNOEXCEPT
    {
        return value? "true" : "false";
    }

    template<class s1, class s2>
    void check(const s1& text, const s2& mask, const bool expected)
    {
        const bool result = me::match_pattern(text, mask);
        ASSERT_TRUE(expected == result) 
            << "me::match_pattern(" << text << ", " << mask << ") "
            << "returned '"  << bool2string(result)   << "', "
            << "expected: '" << bool2string(expected) << "'\n"
        ;
    }

    void check_joker(const char* once_value)
    {
        ASSERT_TRUE( me::match_pattern(once_value, "*"  ));
        ASSERT_TRUE( me::match_pattern(once_value, "**" ));
        ASSERT_TRUE(!me::match_pattern(once_value, "*.*"));
    }

} // namespace
//================================================================================

#ifndef NDEBUG
// --- match_pattern(nullptr, mask)
TEST_COMPONENT(000)
{
    bool re = false;
    ASSERT_DEATH_DEBUG(
        const char* const text = NULL; 
        re = me::match_pattern(text, "*")
    );
    ASSERT_DEATH_DEBUG(
        const wchar_t* const text = NULL; 
        re = me::match_pattern(text, L"*")
    );
	(void) re;
}

// --- match_pattern(mask, nullptr)
TEST_COMPONENT(001)
{
    bool re = false;
    ASSERT_DEATH_DEBUG(
        const char* const mask = NULL; 
        re = me::match_pattern("text", mask)
    );
    ASSERT_DEATH_DEBUG(
        const wchar_t* const mask = NULL; 
        re = me::match_pattern(L"text", mask)
    );
    (void) re;	
}

// --- match_pattern(nullptr, nullptr)
TEST_COMPONENT(002)
{
    bool re = false;
    ASSERT_DEATH_DEBUG(
        const char* const text = NULL; 
        const char* const mask = NULL; 
        re = me::match_pattern(text, mask)
    );
    ASSERT_DEATH_DEBUG(
        const wchar_t* const text = NULL; 
        const wchar_t* const mask = NULL; 
        re = me::match_pattern(text, mask)
    );
    (void) re;	
}
#endif // !!NDEBUG

// --- typical usage
TEST_COMPONENT(003)
{
    check("text" , "te*t" , true );
    check("text" , "te?t" , true );
    check("text" , "t??t" , true );
    check("text" , "text" , true );

    check("tixt" , "te*"  , false);
    check("text" , "te??t", false);
    check("texxt", "te?t" , false);
}
// --- non typical usage
TEST_COMPONENT(004)
{
    ASSERT_TRUE(me::match_pattern(""  , "" ));
    ASSERT_TRUE(me::match_pattern(""  , "*"));

    ASSERT_TRUE(!me::match_pattern("1", "" ));
    ASSERT_TRUE(!me::match_pattern("" , "?"));
}

// --- different variants [1]
TEST_COMPONENT(005)
{
    // ? - once any character
    // * - any charaters

    check(""              , ""          , true );
    check("test"          , "test"      , true );
    check("test"          , "*test"     , true );
    check("test"          , "*est"      , true );
    check("test"          , "?est"      , true );

    check("est"           , "?est"      , false);
    check("test"          , "??est"     , false);
    check("ttest"         , "??est"     , true );

    check("test"          , "test?*"    , false);
    check("test1"         , "test?*"    , true );
    check("test1"         , "test??*"   , false);

    check("image001.png"  , "*imag*.png", true );
    check("image001.png"  , "?mag*.png" , true );
    check("mage001.png"   , "?mag*.png" , false);

    check(".ignore"       , ".*"        , true );
    check(".ig.nore"      , ".*"        , true );

    check("den.lib"       , "?den.lib"  , false);
    check("test.ig.nore"  , "t???.ig.n*", true );

    check("libden.lib"    , "*den.lib"  , true );
    check("mylib.txt"     , "*.txt"     , true );
    check("mylib.txt"     , "m*.t*"     , true );
    check("mylib-32-d.lib", "*-32-d.lib", true );

    check("est"           , "?est"      , false);
    check("test.ig.nore"  , ".*"        , false);
    check("tes.ig.nore"   , "t???.ig.n*", false);
    check("mylib.txt"     , "*.lib"     , false);
    check("lib.txt"       , "m*.t*"     , false);
    check("mylib-32.lib"  , "*-32-d.lib", false);
}

// --- different variants [2]
TEST_COMPONENT(006)
{
    // ? - once any character
    // * - any charaters

    // danger of trigraph
    #ifdef dHAS_CPP11
        check(""              , R"raw(??-22*)raw", false);
        check("-22"           , R"raw(??-22*)raw", false);
        check("A-22"          , R"raw(??-22*)raw", false);
        check("QQ-22"         , R"raw(??-22*)raw", true );
        check("ZZ-22"         , R"raw(??-22*)raw", true );
        check("QQQ-22"        , R"raw(??-22*)raw", false);
        check("TT-22M"        , R"raw(??-22*)raw", true );
        check("TT-22M3"       , R"raw(??-22*)raw", true );
        check("Q-22-TT-22M3"  , R"raw(??-22*)raw", false);
        check("QQ-22-TT-22M3" , R"raw(??-22*)raw", true );
    #else
        const std::string mask = "??" + std::string("-22*");
        check(""              , mask, false);
        check("-22"           , mask, false);
        check("A-22"          , mask, false);
        check("QQ-22"         , mask, true );
        check("ZZ-22"         , mask, true );
        check("QQQ-22"        , mask, false);
        check("TT-22M"        , mask, true );
        check("TT-22M3"       , mask, true );
        check("Q-22-TT-22M3"  , mask, false);
        check("QQ-22-TT-22M3" , mask, true );
    #endif // dHAS_CPP11
}

// --- different variants [3]
TEST_COMPONENT(007)
{
    // ? - once any character
    // * - any charaters

    check(""                   , "*/*/*", false);
    check("A/B"                , "*/*/*", false);
    check("A/B/C"              , "*/*/*", true ); 
    check("AA/BB/CC"           , "*/*/*", true ); 
    check("/BBB/"              , "*/*/*", true ); 
    check("//"                 , "*/*/*", true ); 
    check("A/BB/CCC/DDDD/EEEEE", "*/*/*", true ); 
}

// --- different variants [4]
TEST_COMPONENT(008)
{
    // ? - once any character
    // * - any charaters

    check("lib.txt" , ".*"   , false); 
    check(".lib.txt", ".*"   , true ); 
    check("lib.txt" , "*.txt", true ); 
    check(".lib.txt", "*.txt", true ); 
}

// --- stress-test [1]
TEST_COMPONENT(009)
{
    const char* mask
        = "12345hell*12345hello*123hello";

    // --- маска не совпадет из-за последнего символа
    const char* val1 
        = "12345hello111112345hello123helld";
    check(val1, mask, false); 

    // --- теперь к этой же строке 
    // добавляем подходящие по маске символы
    const char* val2 
        = "12345hello111112345hello123hello";
    check(val2, mask, true); 
}

// --- stress-test [2]
TEST_COMPONENT(010)
{
    const char* mask
        = "12345hell*12345hello";

    const char* val
        = "12345hell 12345helld12345hello";
    check(val, mask, true); 
}

// --- stress-test [3]
TEST_COMPONENT(011)
{
    const char* mask 
        = "12345hell*12345hello*123hello";

    const char* val 
        = "12345hello111112345hello123helld";
    check(val, mask, false); 
}

// --- stress-test [4]
TEST_COMPONENT(012)
{
    const char* mask
        = "12345hell*12345hello*123hello";

    const char* val 
        = "12345hello111112345hello123hello";
    check(val, mask, true); 
}

// --- stress-test [5]
TEST_COMPONENT(013)
{
    const char* mask 
        = "12345hell*12345hello*123hello";

    const char* val 
        = "12345hello111112345hello123helld12345hello";
    check(val, mask, false); 
}

// --- stress-test [6]
TEST_COMPONENT(014)
{
    const char* mask
        = "12345hell*12345hello*123hello";

    const char* val 
        = "12345hello111112345hello12345helld12345hello12345hello";
    check(val, mask, false); 
}

// --- stress-test [7]
TEST_COMPONENT(015)
{
    const char* mask
        = "*aabb*ccc*cccc*xxxx*aa";

    const char* val 
        = "qqaabbccccXwwwwdddccccRsssSccccRxxxx*aaa";
    check(val, mask, true); 
}

// --- "*" or "**" or "*.*"
TEST_COMPONENT(016)
{
    check_joker( ""   );
    check_joker( "A"  );
    check_joker( "ABC");
}

// --- non optimize mask [1]
TEST_COMPONENT(017)
{
    // ? - once any character
    // * - any charaters

    check(""              , ""              , true );
    check("test"          , "test"          , true );
    check("test"          , "***test"       , true );
    check("test"          , "**est"         , true );
    check("test"          , "?est"          , true );

    check("est"           , "?est"          , false);
    check("test"          , "??est"         , false);
    check("ttest"         , "??est"         , true );

    check("test"          , "test?*"        , false);
    check("test1"         , "test?*"        , true );
    check("test1"         , "test??*"       , false);

    check("image001.png"  , "*imag*****.png", true );
    check("image001.png"  , "?mag****.png"  , true );
    check("mage001.png"   , "?mag***.png"   , false);

    check(".ignore"       , ".***"          , true );
    check(".ig.nore"      , ".*****"        , true );

    check("den.lib"       , "?den.lib"      , false);
    check("test.ig.nore"  , "t???.ig.n****" , true );

    check("libden.lib"    , "***den.lib"    , true );
    check("mylib.txt"     , "***.txt"       , true );
    check("mylib.txt"     , "m**.t***"      , true );
    check("mylib-32-d.lib", "**-32-d.lib"   , true );

    check("est"           , "?est"          , false);
    check("test.ig.nore"  , ".***"          , false);
    check("tes.ig.nore"   , "t???.ig.n*****", false);
    check("mylib.txt"     , "***.lib"       , false);
    check("lib.txt"       , "m**.t***"      , false);
    check("mylib-32.lib"  , "****-32-d.lib" , false);
}

// --- non optimize mask [2]
TEST_COMPONENT(018)
{
    // ? - once any character
    // * - any charaters

    check(""              , ""                  , true );
    check("test"          , "test"              , true );
    check("1234test"      , "*?*?*test"         , true );
    check("11test"        , "*??*est"           , true );
    check("test"          , "?est"              , true );

    check("est"           , "?est"              , false);
    check("test"          , "??est"             , false);
    check("ttest"         , "??est"             , true );

    check("test"          , "test?*"            , false);
    check("test123"         , "test???*"        , true );
    check("test1"         , "test??*"           , false);

    check("image001.png"  , "*imag*?*??*?**.png", true );
    check("image001.png"  , "?mag*??**?*.png"   , true );
    check("mage001.png"   , "?mag?***?.png"     , false);

    check(".ignore"       , ".?***"             , true );
    check(".ig.nore"      , ".*****?"           , true );

    check("den.lib"       , "?den.lib"          , false);
    check("test.ig.nore"  , "t???.ig.n**?**"    , true );

    check("libden.lib"    , "***?den.lib"       , true );
    check("mylib.txt"     , "?***.txt"          , true );
    check("mylib.txt"     , "m?**.t***?"        , true );
    check("mylib-32-d.lib", "?**-32-d.lib"      , true );

    check("est"           , "?est"              , false);
    check("test.ig.nore"  , ".***?"             , false);
    check("tes.ig.nore"   , "t???.ig.n***** "   , false);
    check("mylib.txt"     , "?***.lib"          , false);
    check("lib.txt"       , "m**.t***"          , false);
    check("mylib-32.lib"  , "?**??**?-32-d.lib" , false);
}

TEST_COMPONENT(019)
{
    const char* val  = "text11aa";
    const char* mask = "text??*";
    const bool success = me::match_pattern(val, mask);
    ASSERT_TRUE(success);
}

TEST_COMPONENT(020)
{
    const char* val = "text1";
    const char* mask = "text??*";
    const bool success = me::match_pattern(val, mask);
    ASSERT_TRUE(!success);
}

TEST_COMPONENT(021)
{
    const char* mask = "text??*";

    const bool success 
        = me::match_pattern(std::string("text1"), mask);

    ASSERT_TRUE(!success);
}

#endif // !TEST_TOOLS_MATCH_PATTERN



