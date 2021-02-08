
// [2021-02-05] Idrisov Denis R.
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
    typedef ::std::string str_t;
    typedef ::std::wstring str_w;
    typedef ::std::list<str_t> list_t;
    typedef ::std::list<str_w> list_w;

} // namespace
//==============================================================================

#ifndef NDEBUG
// --- nullptr (death)
TEST_COMPONENT(000)
{
    bool re = false;
    ASSERT_DEATH_DEBUG(
        list_t coll;
        const char* mask = NULL;
        re = me::match_pattern("", mask, coll)
    );
    ASSERT_DEATH_DEBUG(
        list_t coll;
        const char* text = NULL;
        const char* mask = NULL;
        re = me::match_pattern(text, mask, coll)
    );

    ASSERT_DEATH_DEBUG(
        list_w coll;
        const wchar_t* mask = NULL;
        re = me::match_pattern(L"", mask, coll)
    );
    ASSERT_DEATH_DEBUG(
        list_w coll;
        const wchar_t* text = NULL;
        const wchar_t* mask = NULL;
        re = me::match_pattern(text, mask, coll)
    );
	(void) re;
}
#endif

// --- different variants
TEST_COMPONENT(001)
{
    const char* mask = "m?lib.*t";
    const char* val = "mylib.txt";
    list_t words;
    
    list_t etalon;
    etalon.push_back("y");
    etalon.push_back("tx");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(words == etalon);
    ASSERT_TRUE(success);
}
TEST_COMPONENT(002)
{
    const char* mask = "";
    const char* val = "";
    list_t words;
    const bool success 
        = me::match_pattern(val, mask, words);

    ASSERT_TRUE(success);
    ASSERT_TRUE(words.empty());
}
TEST_COMPONENT(003)
{
    const char* mask = "test";
    const char* val = "test";
    list_t words;
    const bool success
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words.empty());
}
TEST_COMPONENT(004)
{
    const char* mask = "*test";
    const char* val = "test";
    list_t words;
    list_t etalon;
    etalon.push_back("");
    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(005)
{
    const char* mask = "*?test";
    const char* val = "Ntest";
    list_t words;
    list_t etalon;
    etalon.push_back("");
    etalon.push_back("N");

    const bool success
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(006)
{
    const char* mask = "*est";
    const char* val  = "test";
    list_t words;
    list_t etalon;
    etalon.push_back("t");
    const bool success
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(007)
{
    const char* mask = "?est";
    const char* val = "test";
    list_t words;
    list_t etalon;
    etalon.push_back("t");
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(008)
{
    const char* mask = "?est";
    const char* val = "est";
    list_t words;
    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(!success);
    ASSERT_TRUE(words.empty());
}
TEST_COMPONENT(009)
{
    const char* mask = "*imag*.png";
    const char* val = "image001.png";
    list_t words;

    list_t etalon;
    etalon.push_back("");
    etalon.push_back("e001");
    
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(010)
{
    const char* mask = "ab*?.png";
    const char* val = "abX1.png";
    list_t words;

    list_t etalon;
    etalon.push_back("X");
    etalon.push_back("1");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(011)
{
    const char* mask = "ab*?.png";
    const char* val = "abXD1.png";
    list_t words;

    list_t etalon;
    etalon.push_back("XD");
    etalon.push_back("1");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(012)
{
    const char* mask = "?*imag*?.png";
    const char* val = "Nimage001.png";
    list_t words;

    list_t etalon;
    etalon.push_back("N");
    etalon.push_back("");
    etalon.push_back("e00");
    etalon.push_back("1");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(013)
{
    const char* mask = "?*imag*?.png";
    const char* val = "NABCimage001.png";
    list_t words;

    list_t etalon;
    etalon.push_back("N");
    etalon.push_back("ABC");
    etalon.push_back("e00");
    etalon.push_back("1");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(014)
{
    const char* mask = "?mag*.png";
    const char* val = "image001.png";
    list_t words;

    list_t etalon;
    etalon.push_back("i");
    etalon.push_back("e001");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(015)
{
    const char* mask = "??ag*.png";
    const char* val = "image001.png";
    list_t words;

    list_t etalon;
    etalon.push_back("im");
    etalon.push_back("e001");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(016)
{
    const char* mask = "?mag*.png";
    const char* val = "mage001.png";
    list_t words;

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(!success);
    ASSERT_TRUE(words.empty());
}
TEST_COMPONENT(017)
{
    const char* mask = ".*";
    const char* val = ".ignore";
    list_t words;

    list_t etalon;
    etalon.push_back("ignore");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(018)
{
    const char* mask = ".*";
    const char* val = ".ig.nore";
    list_t words;

    list_t etalon;
    etalon.push_back("ig.nore");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(019)
{
    const char* mask = "?den.lib";
    const char* val = "den.lib";
    list_t words;
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(!success);
    ASSERT_TRUE(words.empty());
}
TEST_COMPONENT(020)
{
    const char* mask = "t???.ig.n*";
    const char* val = "test.ig.nore";
    list_t words;

    list_t etalon;
    etalon.push_back("est");
    etalon.push_back("ore");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(021)
{
    const char* mask = "*den.lib";
    const char* val = "libden.lib";
    list_t words;

    list_t etalon;
    etalon.push_back("lib");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(022)
{
    const char* mask = "*.txt";
    const char* val = "mylib.txt";
    list_t words;

    list_t etalon;
    etalon.push_back("mylib");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(023)
{
    const char* mask = "m*.t*";
    const char* val = "mylib.txt";
    list_t words;

    list_t etalon;
    etalon.push_back("ylib");
    etalon.push_back("xt");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(024)
{
    const char* mask = "*-32-d.l*b";
    const char* val = "mylib-32-d.lib";
    list_t words;

    list_t etalon;
    etalon.push_back("mylib");
    etalon.push_back("i");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(025)
{
    const char* mask = "*aabb*ccc*cccc*xxxx*aa";
    const char* val = "qqaabbccccXwwwwdddccccRsssSccccRxxxx*aaa";
    list_t words;

    list_t etalon;
    etalon.push_back("qq");
    etalon.push_back("");
    etalon.push_back("cXwwwwddd");
    etalon.push_back("RsssSccccR");
    etalon.push_back("*a");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(026)
{
    const char* val = "  #include<ololo> //hello world ";
    const char* mask = "*#include<*>*";
    
    list_t words;

    list_t etalon;
    etalon.push_back("  ");
    etalon.push_back("ololo");
    etalon.push_back(" //hello world ");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(027)
{
    const char* val = "#include<ololo>";
    const char* mask = "#include<*>";
    
    list_t words;

    list_t etalon;
    etalon.push_back("ololo");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(028)
{
    const char* mask = "*aabb*ccc*cccc*xxxx*aa*";
    const char* val = "qqaabbccccXwwwwdddccccRsssSccccRxxxx_aaa";
    list_t words;

    list_t etalon;
    etalon.push_back("qq");
    etalon.push_back("");
    etalon.push_back("cXwwwwddd");
    etalon.push_back("RsssSccccR");
    etalon.push_back("_");
    etalon.push_back("a");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(029)
{
    const char* val = "#include<ololo>";
    const char* mask = "#include*<*>";
    
    list_t words;

    list_t etalon;
    etalon.push_back("");
    etalon.push_back("ololo");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(030)
{
    const char* val = "#include  <ololo> ";
    const char* mask = "*#include*<*>*";
    
    list_t words;

    list_t etalon;
    etalon.push_back("");
    etalon.push_back("  ");
    etalon.push_back("ololo");
    etalon.push_back(" ");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(031)
{
    const char* val = "text11aa";
    const char* mask = "text??*";
    list_t words; 

    list_t etalon;
    etalon.push_back("11");
    etalon.push_back("aa");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(032)
{
    const char* val = "test1";
    const char* mask = "test?*";

    list_t words; 

    list_t etalon;
    etalon.push_back("1");
    etalon.push_back("");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(033)
{
    const char* val = "123AABB";
    const char* mask = "123**B";

    list_t words; 

    list_t etalon;
    etalon.push_back("AAB");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(034)
{
    const char* val = "123AABB";
    const char* mask = "123**";

    list_t words; 

    list_t etalon;
    etalon.push_back("AABB");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(035)
{
    const char* val = "123AAXBB";
    const char* mask = "123*?*";

    list_t words; 

    list_t etalon;
    etalon.push_back("");
    etalon.push_back("A");
    etalon.push_back("AXBB");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(036)
{
    const char* val = "123";
    const char* mask = "123*?*";
    list_t words;
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(!success);
}
TEST_COMPONENT(037)
{
    const char* val = "123A";
    const char* mask = "123*?*";

    list_t words; 

    list_t etalon;
    etalon.push_back("");
    etalon.push_back("A");
    etalon.push_back("");

    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(038)
{
    const char* val = "  #include <ololo> //comment";
    const char* mask = "*#include*<*>*";

    list_t words; 
    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words.size() == 4);

    list_t::const_iterator it = words.begin();
    ++it; ++it;

    const str_t& header = *it;
    ASSERT_TRUE(header == "ololo");
}
TEST_COMPONENT(039)
{
    const char* val = "  AA 8(9)3 AA 8(9)33  ";
    const char* mask = "* AA ?(?)?? *";
    list_t words;

    list_t etalon;
    etalon.push_back("  AA 8(9)3");
    etalon.push_back("8");
    etalon.push_back("9");
    etalon.push_back("33");
    etalon.push_back(" ");

    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(040)
{
    const char* val = "  phone: 8(999)33-22-1 phone: 8(999)33-22-11  ";
    #ifdef dHAS_CPP11
        const char* mask = R"raw(* phone: ?(???)??-??-?? *)raw";
    #else
    // trigraphs
    const str_t mask = "* phone: ?" 
        + std::string("(??")  
        + std::string("?)") 
        + std::string("??") 
        + "-" 
        + std::string("??")
        + "-" 
        + std::string("??")
        +" *";
    #endif
    list_t words;

    list_t etalon;
    etalon.push_back("  phone: 8(999)33-22-1");
    etalon.push_back("8");
    etalon.push_back("999");
    etalon.push_back("33");
    etalon.push_back("22");
    etalon.push_back("11");
    etalon.push_back(" ");

    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(041)
{
    const char* val = "AAxx44hhBB";
    const char* mask = "AA**??**BB";
    list_t words;

    list_t etalon;
    etalon.push_back("");
    etalon.push_back("xx");
    etalon.push_back("44hh");

    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(042)
{
    const char* val = "AA44BB55";
    const char* mask = "AA??BB??";
    list_t words; 

    list_t etalon;
    etalon.push_back("44");
    etalon.push_back("55");

    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(043)
{
    const char* mask = "ab*?*.png";
    const char* val = "abX1Y.png";
    list_t words;

    list_t etalon;
    etalon.push_back("");
    etalon.push_back("X");
    etalon.push_back("1Y");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(044)
{
    const char* mask = "ab*??*.png";
    const char* val = "abX11Y.png";
    list_t words;

    list_t etalon;
    etalon.push_back("");
    etalon.push_back("X1");
    etalon.push_back("1Y");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(045)
{
    const char* mask = "ab*??.png";
    const char* val = "abX11.png";
    list_t words;

    list_t etalon;
    etalon.push_back("X");
    etalon.push_back("11");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(046)
{
    const char* mask = "ab*?1?*.png";
    const char* val =  "abX111d.png";
    list_t words;

    list_t etalon;
    etalon.push_back("");
    etalon.push_back("X");
    etalon.push_back("1");
    etalon.push_back("1d");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(047)
{
    const char* mask = "ab*?1?*.png";
    const char* val =  "abX11d.png";
    list_t words;

    list_t etalon;
    etalon.push_back("");
    etalon.push_back("X");
    etalon.push_back("1");
    etalon.push_back("d");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(048)
{
    const char* mask = "12345hell*12345hello*123hello";
    const char* val =  "12345hello111112345hello123hello";
    list_t words;

    list_t etalon;
    etalon.push_back("o1111");
    etalon.push_back("");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(049)
{
    const char* mask = "12345hell*12345hello*123hello";
    const char* val =  "12345hello111112345helloXXX123hello";
    list_t words;

    list_t etalon;
    etalon.push_back("o1111");
    etalon.push_back("XXX");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(050)
{
    const char* mask = "12345hell*12345hello";
    const char* val = "12345hell 12345helld12345hello";
    list_t words;

    list_t etalon;
    etalon.push_back(" 12345helld");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(051)
{
    const char* mask = "12345hell*12345hello*123hello";
    const char* val = "12345hello111112345hello123hello";
    list_t words;

    list_t etalon;
    etalon.push_back("o1111");
    etalon.push_back("");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(052)
{
    const char* mask = "*aabb*ccc*cccc*xxxx*aa";
    const char* val = "qqaabbccccXwwwwdddccccRsssSccccRxxxx*aaa";    

    list_t words;

    list_t etalon;
    etalon.push_back("qq");
    etalon.push_back("");
    etalon.push_back("cXwwwwddd");
    etalon.push_back("RsssSccccR");
    etalon.push_back("*a");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(053)
{
    const char* mask = "*aabb**ccc**cccc**xxxx**aa";
    const char* val = "qqaabbccccXwwwwdddccccRsssSccccRxxxx*aaa";    

    list_t words;

    list_t etalon;
    etalon.push_back("qq");
    etalon.push_back("");
    etalon.push_back("cXwwwwddd");
    etalon.push_back("RsssSccccR");
    etalon.push_back("*a");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(054)
{
    const char* mask = "*#include<*.??*>*";
    const char* val = "#include<sample.hpp>";    

    list_t words;

    list_t etalon;
    etalon.push_back("");
    etalon.push_back("sample");
    etalon.push_back("hp");
    etalon.push_back("p");
    etalon.push_back("");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(055)
{
    const char* mask = "***#include<****.??***>***";
    const char* val = "#include<sample.hpp>";    

    list_t words;

    list_t etalon;
    etalon.push_back("");
    etalon.push_back("sample");
    etalon.push_back("hp");
    etalon.push_back("p");
    etalon.push_back("");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}

#endif // !TEST_TOOLS_MATCH_PATTERN

