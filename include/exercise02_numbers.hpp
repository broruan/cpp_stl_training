#pragma once

#include <cstddef>
#include <vector>

namespace homework {

struct NumberSummary {
    std::vector<int> sorted;            // 删除负数后的升序序列，保留重复值。
    std::vector<int> unique;            // sorted 的升序去重版本。
    long long sum = 0;                  // sorted 所有元素的和，重复值也参与。
    std::size_t target_count = 0;       // target 在 sorted 中出现的次数。
    std::size_t lower_bound_index = 0;  // sorted 中第一个 >= target 的位置。
};

/*
 * 第 2 题：整理一组数字（基础）
 *
 * 知识点：vector、迭代器区间、remove_if + erase、sort、unique + erase、
 *         count、accumulate、lower_bound。
 * 实现位置：src/exercise02_numbers.cpp。
 *
 * 按以下规则返回 NumberSummary：
 * 1. 删除所有负数，0 必须保留，再升序排序，保存到 sorted。
 * 2. 生成去重后的序列 unique；sorted 本身仍保留重复值。
 * 3. sum 对 sorted 求和；target_count 也在 sorted 中统计。
 * 4. lower_bound_index 是 sorted 中第一个 >= target 的下标。
 *    没有满足条件的元素时，返回 sorted.size()，不要使用 -1。
 * 5. 空输入或全部为负数时：两个序列为空，其余字段均为 0。
 * 6. 不改变调用者传入的 vector。本函数已通过值传递获得一份副本。
 *
 * 示例：numbers = {3, -1, 2, 3, 0}, target = 3
 * 返回 sorted={0,2,3,3}, unique={0,2,3}, sum=8,
 *      target_count=2, lower_bound_index=2。
 *
 * 要求使用上述 STL 算法，不手写排序或二分查找。整体复杂度 O(n log n)。
 * 求和初始值使用 0LL，测试包含结果超过 int 范围的情况。
 * unique/remove_if 不改变 size，必须配合 erase；不得解引用 end()。
 * reserve 只预留容量，不能让不存在的下标变得可写；resize 才改变 size。
 */
NumberSummary summarize_numbers(std::vector<int> numbers, int target);

}  // namespace homework

