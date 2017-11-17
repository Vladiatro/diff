#include <gtest/gtest.h>
#include <main/diff_creators/MaximumMatchDifferenceCreator.h>

TEST(MaximumMatchCreatorTest, get_full_ordered_diff) {
    auto creator = new MaximumMatchDifferenceCreator();

    vector<HashedString> oldStrings;
    oldStrings.emplace_back("a");
    oldStrings.emplace_back("b");
    oldStrings.emplace_back("c");
    oldStrings.emplace_back("d");
    oldStrings.emplace_back("e");

    vector<HashedString> newStrings;
    newStrings.emplace_back("c");
    newStrings.emplace_back("d");
    newStrings.emplace_back("e");
    newStrings.emplace_back("a");
    newStrings.emplace_back("b");

    auto diff = creator->get_full_ordered_diff(&oldStrings, &newStrings);

    vector<FlaggedString> expected;
    expected.emplace_back(FlaggedString("a", LINE_REMOVED));
    expected.emplace_back(FlaggedString("b", LINE_REMOVED));
    expected.emplace_back(FlaggedString("c", LINE_KEPT));
    expected.emplace_back(FlaggedString("d", LINE_KEPT));
    expected.emplace_back(FlaggedString("e", LINE_KEPT));
    expected.emplace_back(FlaggedString("a", LINE_ADDED));
    expected.emplace_back(FlaggedString("b", LINE_ADDED));

    EXPECT_EQ(diff, expected);
}