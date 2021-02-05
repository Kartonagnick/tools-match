
#include <mygtest/modern.hpp>

#ifdef TEST_TOOLS_MATCH_OPTIMIZE_MASK

#define dTEST_COMPONENT tools, match
#define dTEST_METHOD optimize_mask
#define dTEST_TAG tdd

#include <tools/match/optimize_mask.hpp>
namespace me = ::tools;
//==============================================================================
namespace
{
    template<class s1, class s2> 
    void optimization(const s1& src_mask, const s2& expect)
    {
        using x  = decltype(src_mask[0]);
        using z  = std::remove_reference_t<x>;
        using ch = std::remove_cv_t<z>;
        using str_type = std::basic_string<ch>;

        str_type mask = src_mask;
        const size_t len = me::optimize_mask(mask);
        const str_type result(mask, 0, len);

        ASSERT_TRUE(result == expect)
            << "mask = '"     << mask   << "'\n"
            << "expected = '" << expect << "'\n"
        ;
    }

    #define optimize(mask, expect)  \
        optimization(mask, expect); \
        optimization(L##mask, L##expect)
    
} // namespace

//==============================================================================

// nullptr (death)
TEST_COMPONENT(000)
{
    ASSERT_DEATH_DEBUG(
         char* mask = nullptr;
         me::optimize_mask(mask)
    );

    ASSERT_DEATH_DEBUG(
         wchar_t* mask = nullptr;
         me::optimize_mask(mask)
    );
}
TEST_COMPONENT(001)
{
    std::string mask = "1**?a";
    const size_t len = me::optimize_mask(mask);
    ASSERT_TRUE(len == 4);
    ASSERT_TRUE(mask.size() == 4);

    std::string re(mask, 0, len);
    ASSERT_TRUE(re == "1*?a");
    ASSERT_TRUE(mask == "1*?a");
}
TEST_COMPONENT(002)
{
    //             0123456789012345678
    char mask[] = "aaa****bbbb";
    const std::string etalon = "aaa*bbbb";

    const auto len = me::optimize_mask(mask);
    const std::string result(mask, len);
    ASSERT_TRUE(len == etalon.length());
    ASSERT_TRUE(etalon == result);
}
TEST_COMPONENT(003)
{
    //             0123456789012345678
    char mask[] = "aaa****bbbb***ccc";
    const std::string etalon = "aaa*bbbb*ccc";

    const auto len = me::optimize_mask(mask);
    const std::string result(mask, len);
    ASSERT_TRUE(len == etalon.length());
    ASSERT_TRUE(etalon == result);
}
TEST_COMPONENT(004)
{
    char mask[] = "***";
    const std::string etalon = "*";
    const auto len = me::optimize_mask(mask);
    const std::string result(mask, len);
    ASSERT_TRUE(len == etalon.length());
    ASSERT_TRUE(etalon == result);
}
TEST_COMPONENT(005)
{
    char mask[] = "";
    const std::string etalon = "";
    const auto len = me::optimize_mask(mask);
    const std::string result(mask, len);
    ASSERT_TRUE(len == etalon.length());
    ASSERT_TRUE(etalon == result);
}
TEST_COMPONENT(006)
{
    char mask[] = "txt";
    const std::string etalon = "txt";
    const auto len = me::optimize_mask(mask);
    const std::string result(mask, len);
    ASSERT_TRUE(len == etalon.length());
    ASSERT_TRUE(etalon == result);
}
TEST_COMPONENT(007)
{
    std::string mask = "1**?***a*?**";
    const size_t len = me::optimize_mask(mask);
    ASSERT_TRUE(len == 8);
    std::string re(mask, 0, len);
    ASSERT_TRUE(re == "1*?*a*?*");
    ASSERT_TRUE(mask == "1*?*a*?*");
}
TEST_COMPONENT(008)
{
    std::string val = "123???***??456";
    me::optimize_mask(val);
    ASSERT_TRUE(val == "123???*??456");
}

// --- stress
TEST_COMPONENT(009)
{
    optimize("*.*"            , "*.*"             );
    optimize(""               ,  ""               );
    optimize("**?test??.** /" ,  "*?test??.* /"   );
    optimize("*?m.?*"         ,  "*?m.?*"         );
    optimize("*?m.?*/"        ,  "*?m.?*/"        );
    optimize("*?m.?* /"       ,  "*?m.?* /"       );
    optimize("  *?m.?* /"     ,  "  *?m.?* /"     );
    optimize("*?m.?"          ,  "*?m.?"          );
    optimize("*?m.?/"         ,  "*?m.?/"         );
    optimize("*?m.? /"        ,  "*?m.? /"        );
    optimize("  *?m.? /"      ,  "  *?m.? /"      );
    optimize("  *?m.? "       ,  "  *?m.? "       );
    optimize("*?m.??"         ,  "*?m.??"         );
    optimize(" *?m.?? "       ,  " *?m.?? "       );
    optimize(" *?m.?? /"      ,  " *?m.?? /"      );
    optimize("*?m.\?\?"       ,  "*?m.\?\?"       );
    optimize("*?m.\?\? "      ,  "*?m.\?\? "      );
    optimize("*?m.?*?"        ,  "*?m.?*?"        );
    optimize("  *?m.?*?  "    ,  "  *?m.?*?  "    );
    optimize(" *?m.?*?/"      ,  " *?m.?*?/"      );
    optimize(" *?m.?*? /"     ,  " *?m.?*? /"     );
    optimize("*?m.?*?/ "      ,  "*?m.?*?/ "      );
    optimize("  *?m.?*?  /  " ,  "  *?m.?*?  /  " );
    optimize("  *?m.?*?"      ,  "  *?m.?*?"      );
    optimize("  *?m.?*?/"     ,  "  *?m.?*?/"     );
    optimize("  *?m.?*? /"    ,  "  *?m.?*? /"    );
    optimize("  *?m.?*? / "   ,  "  *?m.?*? / "   );
    optimize("  *?m.?*? //"   ,  "  *?m.?*? //"   );
    optimize("  *?m.?*?/ "    ,  "  *?m.?*?/ "    );
    optimize("  *?m.?*?  "    ,  "  *?m.?*?  "    );
    optimize("  *?m.?*?  /"   ,  "  *?m.?*?  /"   );
    optimize("  *?m.?*?  / "  ,  "  *?m.?*?  / "  );
    optimize("  *?m.?*?/  "   ,  "  *?m.?*?/  "   );
    optimize("  ***?m.?***?/  " ,  "  *?m.?*?/  " );
}

#endif // !TEST_TOOLS_MATCH_OPTIMIZE_MASK


