#pragma once

#include <string>

namespace homework {

/*
 * 第 3 题：判断括号是否匹配（基础应用）
 *
 * 知识点：string 遍历、stack、后进先出、empty/top/pop。
 * 实现位置：src/exercise03_brackets.cpp。
 *
 * 1. 只检查 ()、[]、{} 三种括号，其他字符一律忽略。
 *    不分析引号、注释等语法；例如引号里的括号也参加匹配。
 * 2. 左右括号数量、类型和嵌套顺序都正确时返回 true，否则返回 false。
 * 3. 空字符串或没有括号的字符串返回 true。
 *
 * 示例："a + (b * [c - d])" -> true
 *       "{[()]}" -> true；"([)]" -> false；"(()" -> false。
 *
 * 要求使用 std::stack<char>，一次从左到右扫描，时间复杂度 O(n)。
 * 提示：左括号入栈；右括号与栈顶配对；扫描完成时栈必须为空。
 * 调用 top/pop 前先判断 empty；pop() 只删除元素，不返回被删除的值。
 * 不要求编写表达式计算器。
 */
bool brackets_match(const std::string& text);

}  // namespace homework

