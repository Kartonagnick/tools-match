
// [2021-02-05] Idrisov Denis R.
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_MATCH_PATTERN

#define dTEST_COMPONENT tools, match
#define dTEST_METHOD match_pattern
#define dTEST_TAG vector

#include <tools/match/pattern.hpp>

#include <string>
#include <vector>
namespace me = ::tools;
//==============================================================================
namespace
{
    typedef ::std::string str_t;
    typedef ::std::wstring str_w;
    typedef ::std::vector<str_t> vec_t;
    typedef ::std::vector<str_w> vec_w;
	
	template<class cont, class s1, class s2>
	void test_death(const s1& text, const s2& mask)
	{
		cont coll;
		const bool re
		    = me::match_pattern(text, mask, coll);
		(void) re;
	}
	

} // namespace
//==============================================================================

#ifndef NDEBUG
// --- nullptr (death)
TEST_COMPONENT(000)
{
	ASSERT_DEATH_DEBUG(
	    const char* mask = NULL;
	    test_death<vec_t>("", mask)
	);
	ASSERT_DEATH_DEBUG(
	    const char* text = NULL;
	    const char* mask = NULL;
	    test_death<vec_t>(text, mask)
	);
	
	ASSERT_DEATH_DEBUG(
	    const wchar_t* mask = NULL;
        test_death<vec_w>(L"", mask)
	);
	ASSERT_DEATH_DEBUG(
	    const wchar_t* text = NULL;
	    const wchar_t* mask = NULL;
	    test_death<vec_w>(text, mask)
	);
}
#endif

// --- different variants
TEST_COMPONENT(001)
{
    const char* mask = "m?lib.*t";
    const char* val = "mylib.txt";
    vec_t words;
    
    vec_t etalon;
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
    vec_t words;
    const bool success 
        = me::match_pattern(val, mask, words);

    ASSERT_TRUE(success);
    ASSERT_TRUE(words.empty());
}
TEST_COMPONENT(003)
{
    const char* mask = "test";
    const char* val = "test";
    vec_t words;
    const bool success
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words.empty());
}
TEST_COMPONENT(004)
{
    const char* mask = "*test";
    const char* val = "test";
    vec_t words;
    vec_t etalon;
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
    vec_t words;
    vec_t etalon;
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
    vec_t words;
    vec_t etalon;
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
    vec_t words;
    vec_t etalon;
    etalon.push_back("t");
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(008)
{
    const char* mask = "?est";
    const char* val = "est";
    vec_t words;
    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(!success);
    ASSERT_TRUE(words.empty());
}
TEST_COMPONENT(009)
{
    const char* mask = "*imag*.png";
    const char* val = "image001.png";
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(!success);
    ASSERT_TRUE(words.empty());
}
TEST_COMPONENT(017)
{
    const char* mask = ".*";
    const char* val = ".ignore";
    vec_t words;

    vec_t etalon;
    etalon.push_back("ignore");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(018)
{
    const char* mask = ".*";
    const char* val = ".ig.nore";
    vec_t words;

    vec_t etalon;
    etalon.push_back("ig.nore");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(019)
{
    const char* mask = "?den.lib";
    const char* val = "den.lib";
    vec_t words;
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(!success);
    ASSERT_TRUE(words.empty());
}
TEST_COMPONENT(020)
{
    const char* mask = "t???.ig.n*";
    const char* val = "test.ig.nore";
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
    etalon.push_back("lib");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(022)
{
    const char* mask = "*.txt";
    const char* val = "mylib.txt";
    vec_t words;

    vec_t etalon;
    etalon.push_back("mylib");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(023)
{
    const char* mask = "m*.t*";
    const char* val = "mylib.txt";
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
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
    
    vec_t words;

    vec_t etalon;
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
    
    vec_t words;

    vec_t etalon;
    etalon.push_back("ololo");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(028)
{
    const char* mask = "*aabb*ccc*cccc*xxxx*aa*";
    const char* val = "qqaabbccccXwwwwdddccccRsssSccccRxxxx_aaa";
    vec_t words;

    vec_t etalon;
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
    
    vec_t words;

    vec_t etalon;
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
    
    vec_t words;

    vec_t etalon;
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
    vec_t words; words.reserve(2);

    vec_t etalon;
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

    vec_t words; words.reserve(2);

    vec_t etalon;
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

    vec_t words; words.reserve(2);

    vec_t etalon;
    etalon.push_back("AAB");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(034)
{
    const char* val = "123AABB";
    const char* mask = "123**";

    vec_t words; words.reserve(2);

    vec_t etalon;
    etalon.push_back("AABB");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(035)
{
    const char* val = "123AAXBB";
    const char* mask = "123*?*";

    vec_t words; words.reserve(2);

    vec_t etalon;
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
    vec_t words;
    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(!success);
}
TEST_COMPONENT(037)
{
    const char* val = "123A";
    const char* mask = "123*?*";

    vec_t words; words.reserve(3);

    vec_t etalon;
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

    vec_t words; words.reserve(4);
    const bool success 
        = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words.size() == 4);
    const str_t& header = words[2];
    ASSERT_TRUE(header == "ololo");
}
TEST_COMPONENT(039)
{
    const char* val = "  AA 8(9)3 AA 8(9)33  ";
    const char* mask = "* AA ?(?)?? *";
    vec_t words;

    vec_t etalon;
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
    vec_t words; words.reserve(10);

    vec_t etalon;
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
    vec_t words; words.reserve(10);

    vec_t etalon;
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
    vec_t words; words.reserve(10);

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
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
    vec_t words;

    vec_t etalon;
    etalon.push_back(" 12345helld");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}
TEST_COMPONENT(051)
{
    const char* mask = "12345hell*12345hello*123hello";
    const char* val = "12345hello111112345hello123hello";
    vec_t words;

    vec_t etalon;
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

    vec_t words;

    vec_t etalon;
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

    vec_t words;

    vec_t etalon;
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

    vec_t words;

    vec_t etalon;
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

    vec_t words;

    vec_t etalon;
    etalon.push_back("");
    etalon.push_back("sample");
    etalon.push_back("hp");
    etalon.push_back("p");
    etalon.push_back("");

    const bool success = me::match_pattern(val, mask, words);
    ASSERT_TRUE(success);
    ASSERT_TRUE(words == etalon);
}

//==============================================================================
#endif // !TEST_TOOLS_MATCH_PATTERN
