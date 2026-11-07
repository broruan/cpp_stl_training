#include "exercise02_numbers.hpp"

#include <gtest/gtest.h>

#include <limits>

namespace homework {
namespace {

void expect_summary(const NumberSummary& actual, const std::vector<int>& sorted,
                    const std::vector<int>& unique, long long sum,
                    std::size_t count, std::size_t index) {
    EXPECT_EQ(actual.sorted, sorted);
    EXPECT_EQ(actual.unique, unique);
    EXPECT_EQ(actual.sum, sum);
    EXPECT_EQ(actual.target_count, count);
    EXPECT_EQ(actual.lower_bound_index, index);
}

}  // namespace

TEST(Ex02Numbers, MatchesExample) {
    expect_summary(summarize_numbers({3, -1, 2, 3, 0}, 3),
                   {0, 2, 3, 3}, {0, 2, 3}, 8, 2, 2);
}

TEST(Ex02Numbers, EmptyInput) {
    expect_summary(summarize_numbers({}, 5), {}, {}, 0, 0, 0);
}

TEST(Ex02Numbers, AllNegativeValuesAreRemoved) {
    expect_summary(summarize_numbers({-1, -5, -1}, -1), {}, {}, 0, 0, 0);
}

TEST(Ex02Numbers, ZeroAndDuplicatesArePreservedInSorted) {
    expect_summary(summarize_numbers({0, 0, -2, 0}, 0), {0, 0, 0}, {0}, 0, 3, 0);
}

TEST(Ex02Numbers, MissingTargetBetweenElements) {
    expect_summary(summarize_numbers({7, 2, 4, 2}, 3),
                   {2, 2, 4, 7}, {2, 4, 7}, 15, 0, 2);
}

TEST(Ex02Numbers, TargetBelowMinimum) {
    expect_summary(summarize_numbers({2, 1}, -3), {1, 2}, {1, 2}, 3, 0, 0);
}

TEST(Ex02Numbers, TargetAboveMaximumReturnsSize) {
    expect_summary(summarize_numbers({2, 1, 2}, 8), {1, 2, 2}, {1, 2}, 5, 0, 3);
}

TEST(Ex02Numbers, SumUsesLongLongDuringAccumulation) {
    const int largest = std::numeric_limits<int>::max();
    expect_summary(summarize_numbers({largest, largest, 1}, largest),
                   {1, largest, largest}, {1, largest},
                   2LL * largest + 1, 2, 1);
}

TEST(Ex02Numbers, DoesNotModifyCallerInput) {
    const std::vector<int> input{3, -1, 2, 3};
    const auto result = summarize_numbers(input, 2);
    EXPECT_EQ(input, (std::vector<int>{3, -1, 2, 3}));
    EXPECT_EQ(result.sorted, (std::vector<int>{2, 3, 3}));
}

}  // namespace homework

