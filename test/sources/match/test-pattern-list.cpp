
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_MATCH_PATTERN

#define dTEST_COMPONENT tools, match
#define dTEST_METHOD match_pattern
#define dTEST_TAG list

#include <tools/match/pattern.hpp>

#include <string>
#include <list>

namespace me = ::tools;
//==============================================================================
namespace
{
    using str_t  = ::std::string;
    using str_w  = ::std::wstring;
    using list_t = ::std::list<str_t>;
    using list_w = ::std::list<str_w>;

} // namespace
//==============================================================================

// --- nullptr (death)
TEST_COMPONENT(000)
{
    ASSERT_DEATH_DEBUG(
        list_t coll;
        const char* text = nullptr;
        me::match_pattern(text, "", coll)
    );
    ASSERT_DEATH_DEBUG(
        list_w coll;
        const wchar_t* text = nullptr;
        me::match_pattern(text, L"", coll)
    );
}

// --- different variants
TEST_COMPONENT(001)
{
    const auto* mask = "m?lib.*t";
    const auto* val = "mylib.txt";
    list_t words;
    const list_t etalon = { "y", "tx" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(me::match_pattern(val, mask, words));
    ASSERT_TRUE(words == etalon);
    ASSERT_TRUE(success);
}
TEST_COMPONENT(002)
{
    const auto* mask = "";
    const auto* val = "";
    list_t words;
    const bool success 
        = me::match_pattern(val, mask, words);

    ASSERT_TRUE(success);
    ASSERT_TRUE(words.empty());
}
TEST_COMPONENT(003)
{
    const auto* mask = "test";
    const auto* val = "test";
    list_t words;
    const bool success
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words.empty());
}
TEST_COMPONENT(004)
{
    const auto* mask = "*test";
    const auto* val = "test";
    list_t words;
    const list_t etalon = { "" };
    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(005)
{
    const auto* mask = "*?test";
    const auto* val = "Ntest";
    list_t words;
    const list_t etalon = { "", "N" };
    const bool success
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(006)
{
    const auto* mask = "*est";
    const auto* val  = "test";
    list_t words;
    const list_t etalon = { "t" };
    const bool success
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(007)
{
    const auto* mask = "?est";
    const auto* val = "test";
    list_t words;
    const list_t etalon = { "t" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(008)
{
    const auto* mask = "?est";
    const auto* val = "est";
    list_t words;
    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(!success);
    ASSERT_TRUE(words.empty());
}
TEST_COMPONENT(009)
{
    const auto* mask = "*imag*.png";
    const auto* val = "image001.png";
    list_t words;
    const list_t etalon = { "", "e001" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(010)
{
    const auto* mask = "ab*?.png";
    const auto* val = "abX1.png";
    list_t words;
    const list_t etalon = { "X", "1" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(011)
{
    const auto* mask = "ab*?.png";
    const auto* val = "abXD1.png";
    list_t words;
    const list_t etalon = { "XD", "1" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(012)
{
    const auto* mask = "?*imag*?.png";
    const auto* val = "Nimage001.png";
    list_t words;
    const list_t etalon = { "N","", "e00", "1" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(013)
{
    const auto* mask = "?*imag*?.png";
    const auto* val = "NABCimage001.png";
    list_t words;
    const list_t etalon = { "N","ABC", "e00", "1" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(014)
{
    const auto* mask = "?mag*.png";
    const auto* val = "image001.png";
    list_t words;
    const list_t etalon = { "i", "e001" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(015)
{
    const auto* mask = "??ag*.png";
    const auto* val = "image001.png";
    list_t words;
    const list_t etalon = { "im", "e001" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(016)
{
    const auto* mask = "?mag*.png";
    const auto* val = "mage001.png";
    list_t words;
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(!success);
    ASSERT_TRUE(words.empty());
}
TEST_COMPONENT(017)
{
    const auto* mask = ".*";
    const auto* val = ".ignore";
    list_t words;
    const list_t etalon = { "ignore" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(018)
{
    const auto* mask = ".*";
    const auto* val = ".ig.nore";
    list_t words;
    const list_t etalon = { "ig.nore" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(019)
{
    const auto* mask = "?den.lib";
    const auto* val = "den.lib";
    list_t words;
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(!success);
    ASSERT_TRUE(words.empty());
}
TEST_COMPONENT(020)
{
    const auto* mask = "t???.ig.n*";
    const auto* val = "test.ig.nore";
    list_t words;
    const list_t etalon = { "est", "ore" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(021)
{
    const auto* mask = "*den.lib";
    const auto* val = "libden.lib";
    list_t words;
    const list_t etalon = { "lib" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(022)
{
    const auto* mask = "*.txt";
    const auto* val = "mylib.txt";
    list_t words;
    const list_t etalon = { "mylib" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(023)
{
    const auto* mask = "m*.t*";
    const auto* val = "mylib.txt";
    list_t words;
    const list_t etalon = { "ylib", "xt" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(024)
{
    const auto* mask = "*-32-d.l*b";
    const auto* val = "mylib-32-d.lib";
    list_t words;
    const list_t etalon = { "mylib", "i" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(025)
{
    const auto* mask = "*aabb*ccc*cccc*xxxx*aa";
    const auto* val = "qqaabbccccXwwwwdddccccRsssSccccRxxxx*aaa";
    list_t words;
    const list_t etalon = { "qq", "", "cXwwwwddd", "RsssSccccR", "*a" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(026)
{
    const auto* val = "  #include<ololo> //hello world ";
    const auto* mask = "*#include<*>*";
    
    list_t words;
    const list_t etalon = { "  ", "ololo", " //hello world " };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(027)
{
    const auto* val = "#include<ololo>";
    const auto* mask = "#include<*>";
    
    list_t words;
    const list_t etalon = { "ololo" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(028)
{
    const auto* mask = "*aabb*ccc*cccc*xxxx*aa*";
    const auto* val = "qqaabbccccXwwwwdddccccRsssSccccRxxxx_aaa";
    list_t words;
    const list_t etalon = { "qq", "", "cXwwwwddd", "RsssSccccR", "_", "a" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(029)
{
    const auto* val = "#include<ololo>";
    const auto* mask = "#include*<*>";
    
    list_t words;
    const list_t etalon = { "", "ololo" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(030)
{
    const auto* val = "#include  <ololo> ";
    const auto* mask = "*#include*<*>*";
    
    list_t words;
    const list_t etalon = {"", "  ", "ololo", " "};
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(031)
{
    const auto* val = "text11aa";
    const auto* mask = "text??*";
    list_t words; 
    const list_t etalon = {"11", "aa"};
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(032)
{
    const auto* val = "test1";
    const auto* mask = "test?*";

    list_t words; 
    const list_t etalon = {"1", ""};
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(033)
{
    const auto* val = "123AABB";
    const auto* mask = "123**B";

    list_t words;
    const list_t etalon = {"AAB"};
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(034)
{
    const auto* val = "123AABB";
    const auto* mask = "123**";

    list_t words; 
    const list_t etalon = {"AABB"};
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(035)
{
    const auto* val = "123AAXBB";
    const auto* mask = "123*?*";

    list_t words;
    const list_t etalon = {"", "A", "AXBB"};
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(036)
{
    const auto* val = "123";
    const auto* mask = "123*?*";
    list_t words;
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(!success);
}
TEST_COMPONENT(037)
{
    const auto* val = "123A";
    const auto* mask = "123*?*";

    list_t words;
    const list_t etalon = {"", "A", ""};
    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(038)
{
    const auto* val = "  #include <ololo> //comment";
    const auto* mask = "*#include*<*>*";

    list_t words; 
    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words.size() == 4);

    auto it = words.cbegin();
    ++it;
    ++it;
    const auto& header = *it;
    ASSERT_TRUE(header == "ololo");
}
TEST_COMPONENT(039)
{
    const auto* val = "  AA 8(9)3 AA 8(9)33  ";
    const auto* mask = "* AA ?(?)?? *";
    list_t words;
    const list_t etalon 
        = {"  AA 8(9)3", "8", "9", "33", " " };
    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(040)
{
    const auto* val = "  phone: 8(999)33-22-1 phone: 8(999)33-22-11  ";
    const auto* mask = R"raw(* phone: ?(???)??-??-?? *)raw";
    list_t words; 
    const list_t etalon 
        = {"  phone: 8(999)33-22-1", "8", "999", "33", "22", "11", " " };
    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(041)
{
    const auto* val = "AAxx44hhBB";
    const auto* mask = "AA**??**BB";
    list_t words; 
    const list_t etalon = { "", "xx", "44hh" };
    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(042)
{
    const auto* val = "AA44BB55";
    const auto* mask = "AA??BB??";
    list_t words; 
    const list_t etalon = { "44", "55" };
    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(043)
{
    const auto* mask = "ab*?*.png";
    const auto* val = "abX1Y.png";
    list_t words;
    const list_t etalon = { "", "X", "1Y" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(044)
{
    const auto* mask = "ab*??*.png";
    const auto* val = "abX11Y.png";
    list_t words;
    const list_t etalon = { "", "X1", "1Y" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(045)
{
    const auto* mask = "ab*??.png";
    const auto* val = "abX11.png";
    list_t words;
    const list_t etalon = { "X", "11", };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(046)
{
    const auto* mask = "ab*?1?*.png";
    const auto* val =  "abX111d.png";
    list_t words;
    const list_t etalon = { "", "X", "1", "1d" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(047)
{
    const auto* mask = "ab*?1?*.png";
    const auto* val =  "abX11d.png";
    list_t words;
    const list_t etalon = { "", "X", "1", "d" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(048)
{
    const auto* mask = "12345hell*12345hello*123hello";
    const auto* val =  "12345hello111112345hello123hello";
    list_t words;
    const list_t etalon = { "o1111", "" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(049)
{
    const auto* mask = "12345hell*12345hello*123hello";
    const auto* val =  "12345hello111112345helloXXX123hello";
    list_t words;
    const list_t etalon = { "o1111", "XXX" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(050)
{
    const auto* mask = "12345hell*12345hello";
    const auto* val = "12345hell 12345helld12345hello";
    list_t words;
    const list_t etalon = { " 12345helld" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(051)
{
    const auto* mask = "12345hell*12345hello*123hello";
    const auto* val = "12345hello111112345hello123hello";
    list_t words;
    const list_t etalon = { "o1111", "" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(052)
{
    const auto* mask = "*aabb*ccc*cccc*xxxx*aa";
    const auto* val = "qqaabbccccXwwwwdddccccRsssSccccRxxxx*aaa";    

    list_t words;
    const list_t etalon = { "qq", "", "cXwwwwddd", "RsssSccccR", "*a" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(053)
{
    const auto* mask = "*aabb**ccc**cccc**xxxx**aa";
    const auto* val = "qqaabbccccXwwwwdddccccRsssSccccRxxxx*aaa";    

    list_t words;
    const list_t etalon = { "qq", "", "cXwwwwddd", "RsssSccccR", "*a" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(054)
{
    const auto* mask = "*#include<*.??*>*";
    const auto* val = "#include<sample.hpp>";    

    list_t words;
    const list_t etalon = { "", "sample", "hp", "p", "" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(055)
{
    const auto* mask = "***#include<****.??***>***";
    const auto* val = "#include<sample.hpp>";    

    list_t words;
    const list_t etalon = { "", "sample", "hp", "p", "" };
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}

#endif // !TEST_TOOLS_MATCH_PATTERN

