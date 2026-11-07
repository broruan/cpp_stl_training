#include "exercise04_words.hpp"

#include <gtest/gtest.h>

namespace homework {

TEST(Ex04Words, CountsWordsAndKeepsUniqueSortedWords) {
    const auto stats = count_words({"pear", "apple", "pear", "", "Apple"});
    const std::unordered_map<std::string, int> expected_counts{
        {"pear", 2}, {"apple", 1}, {"Apple", 1}};
    EXPECT_EQ(stats.counts, expected_counts);
    EXPECT_EQ(stats.unique_words, (std::set<std::string>{"Apple", "apple", "pear"}));
    // 将有序容器转为 vector，直接验证遍历顺序。
    const std::vector<std::string> ordered(stats.unique_words.begin(),
                                           stats.unique_words.end());
    EXPECT_EQ(ordered, (std::vector<std::string>{"Apple", "apple", "pear"}));
}

TEST(Ex04Words, EmptyInputAndEmptyStringsProduceEmptyStats) {
    const auto empty = count_words({});
    EXPECT_TRUE(empty.counts.empty());
    EXPECT_TRUE(empty.unique_words.empty());
    const auto blanks = count_words({"", "", ""});
    EXPECT_TRUE(blanks.counts.empty());
    EXPECT_TRUE(blanks.unique_words.empty());
}

TEST(Ex04Words, DoesNotNormalizeCaseSpacesOrPunctuation) {
    const auto stats = count_words({"apple", "Apple", "apple!", " ", "two words"});
    const std::unordered_map<std::string, int> expected{
        {"apple", 1}, {"Apple", 1}, {"apple!", 1}, {" ", 1}, {"two words", 1}};
    EXPECT_EQ(stats.counts, expected);
    EXPECT_EQ(stats.unique_words.size(), 5U);
}

TEST(Ex04Words, RepeatedCallsDoNotAccumulateOldCounts) {
    const auto first = count_words({"a", "a", "a"});
    const auto second = count_words({"b"});
    EXPECT_EQ(first.counts, (std::unordered_map<std::string, int>{{"a", 3}}));
    EXPECT_EQ(second.counts, (std::unordered_map<std::string, int>{{"b", 1}}));
    EXPECT_EQ(second.unique_words, (std::set<std::string>{"b"}));
}

// 查询测试直接构造数据，便于独立完成 count_of 后单独运行。
TEST(Ex04Words, QueriesExistingAndMissingWordsWithoutInserting) {
    WordStats stats{{{"apple", 2}, {"pear", 1}}, {"apple", "pear"}};
    const auto original_counts = stats.counts;
    const auto original_words = stats.unique_words;
    EXPECT_EQ(count_of(stats, "apple"), 2);
    EXPECT_EQ(count_of(stats, "banana"), 0);
    EXPECT_EQ(count_of(stats, ""), 0);
    EXPECT_EQ(stats.counts, original_counts);
    EXPECT_EQ(stats.unique_words, original_words);
}

TEST(Ex04Words, QueriesEmptyStats) {
    EXPECT_EQ(count_of(WordStats{}, "anything"), 0);
}

TEST(Ex04Words, OrderedCountsPreserveAllValuesInKeyOrder) {
    const WordStats stats{{{"pear", 3}, {"Apple", 1}, {"apple", 2}},
                          {"Apple", "apple", "pear"}};
    const auto result = ordered_counts(stats);
    const std::map<std::string, int> expected{{"Apple", 1}, {"apple", 2}, {"pear", 3}};
    EXPECT_EQ(result, expected);
    std::vector<std::string> keys;
    for (const auto& [word, count] : result) {
        keys.push_back(word);
        EXPECT_GT(count, 0);
    }
    EXPECT_EQ(keys, (std::vector<std::string>{"Apple", "apple", "pear"}));
    EXPECT_EQ(stats.counts.size(), 3U);
}

TEST(Ex04Words, OrderedCountsHandleEmptyStats) {
    EXPECT_TRUE(ordered_counts(WordStats{}).empty());
}

}  // namespace homework

