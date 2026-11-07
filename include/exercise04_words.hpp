#pragma once

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace homework {

struct WordStats {
    std::unordered_map<std::string, int> counts;  // 单词 -> 出现次数，无遍历顺序保证。
    std::set<std::string> unique_words;           // 去重单词，按字典序排列。
};

/*
 * 第 4 题：词频统计与查询（容器组合）
 *
 * 知识点：string、unordered_map、set、map、find 与 operator[] 的区别。
 * 实现位置：src/exercise04_words.cpp。
 *
 * A. count_words(words)
 *    输入已经分词，不需要拆分句子。只忽略空字符串 ""。
 *    其余字符串原样作为键，不去空格、不删除标点，区分大小写。
 *    使用 unordered_map 统计次数，使用 set 保存不重复的单词。
 *    示例：{"pear", "apple", "pear", "", "Apple"}
 *    counts 为 pear:2、apple:1、Apple:1；unique_words 遍历结果为
 *    {"Apple", "apple", "pear"}。空输入返回两个空容器。
 *
 * B. count_of(stats, word)
 *    返回单词次数；不存在时返回 0。查询不能插入新键或改变已有统计。
 *    提示：使用 find()，不要用会插入键的 operator[]。
 *
 * C. ordered_counts(stats)
 *    将 counts 转为 std::map<std::string, int> 并返回。
 *    所有键和值必须保留，遍历结果按单词字典序排列，不修改 stats。
 *    提示：可以用迭代器区间构造 map，也可以逐项插入。
 *
 * 输入最多 10000 个字符串，次数用 int 即可。主要测试英文单词。
 * 不可依赖 unordered_map 的遍历顺序；使用 C++17 的 find，不使用 contains。
 */
WordStats count_words(const std::vector<std::string>& words);
int count_of(const WordStats& stats, const std::string& word);
std::map<std::string, int> ordered_counts(const WordStats& stats);

}  // namespace homework

