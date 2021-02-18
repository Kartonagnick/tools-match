
// [2021y-02m-05d] Idrisov Denis R.
#include <mygtest/test-list.hpp>

#ifdef TEST_TOOLS_MATCH_GROUP

#include <tools/match/group.hpp>

#define TEST_CASE_NAME tools
#define TEST_NUMBER(n) match_group_plus##n

namespace me = ::TEST_CASE_NAME;
//==============================================================================
namespace {} // namespace

//==============================================================================

TEST_COMPONENT(000)
{
    //const auto ok = me::match_group("cy-a", "sv-*, *-a-*, *-a, a-*");
    //ASSERT_TRUE(ok);
}


#endif // !TEST_TOOLS_MATCH_GROUP


