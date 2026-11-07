#include "exercise03_brackets.hpp"

#include <gtest/gtest.h>

namespace homework {

TEST(Ex03Brackets, EmptyOrOrdinaryTextIsValid) {
    EXPECT_TRUE(brackets_match(""));
    EXPECT_TRUE(brackets_match("hello + 123"));
}

TEST(Ex03Brackets, SupportsEachBracketTypeAndAdjacentPairs) {
    EXPECT_TRUE(brackets_match("()"));
    EXPECT_TRUE(brackets_match("[]"));
    EXPECT_TRUE(brackets_match("{}"));
    EXPECT_TRUE(brackets_match("()[]{}"));
}

TEST(Ex03Brackets, SupportsNestedBracketsAndIgnoredText) {
    EXPECT_TRUE(brackets_match("{[()]}"));
    EXPECT_TRUE(brackets_match("a + (b * [c - d])"));
    EXPECT_TRUE(brackets_match("[a\n{b\tc}](d)"));
}

TEST(Ex03Brackets, RejectsCrossedOrWrongTypes) {
    EXPECT_FALSE(brackets_match("([)]"));
    EXPECT_FALSE(brackets_match("(]"));
    EXPECT_FALSE(brackets_match("{)"));
    EXPECT_FALSE(brackets_match("[}"));
}

TEST(Ex03Brackets, RejectsUnexpectedClosingBrackets) {
    EXPECT_FALSE(brackets_match(")"));
    EXPECT_FALSE(brackets_match("]"));
    EXPECT_FALSE(brackets_match("}"));
    EXPECT_FALSE(brackets_match("()[]}"));
    EXPECT_FALSE(brackets_match(")("));
}

TEST(Ex03Brackets, RejectsUnclosedOpeningBrackets) {
    EXPECT_FALSE(brackets_match("("));
    EXPECT_FALSE(brackets_match("["));
    EXPECT_FALSE(brackets_match("{"));
    EXPECT_FALSE(brackets_match("(()"));
    EXPECT_FALSE(brackets_match("{}["));
}

TEST(Ex03Brackets, QuotesDoNotChangeBracketRules) {
    EXPECT_FALSE(brackets_match("\"(\""));
    EXPECT_TRUE(brackets_match("\"()\""));
}

TEST(Ex03Brackets, RepeatedCallsHaveIndependentStacks) {
    EXPECT_FALSE(brackets_match("(("));
    EXPECT_TRUE(brackets_match("[]"));
    EXPECT_FALSE(brackets_match("))"));
}

}  // namespace homework

