#pragma once

#include <deque>
#include <list>
#include <unordered_set>

namespace homework {

struct Task {
    int id;
    int priority;
};

// 已提供比较器，无需修改：优先级越大越先执行；同优先级时 id 越小越先执行。
// priority_queue 的比较器返回 true，表示左侧任务的排序优先程度低于右侧。
struct TaskLowerPriority {
    bool operator()(const Task& lhs, const Task& rhs) const {
        if (lhs.priority != rhs.priority) {
            return lhs.priority < rhs.priority;
        }
        return lhs.id > rhs.id;
    }
};

/*
 * 第 5 题：简单任务调度（小型综合）
 *
 * 知识点：list、迭代器安全删除、unordered_set、queue、priority_queue、deque。
 * 实现位置：src/exercise05_tasks.cpp。没有并发、时间模拟或手写堆的要求。
 *
 * 输入任务的 id 是互不重复的正整数，priority 可以为负数、0 或正数。
 * list 中的顺序就是任务到达顺序。
 *
 * A. remove_cancelled(tasks, cancelled_ids)
 *    删除 id 出现在 cancelled_ids 中的任务，保留其余任务的相对顺序和字段。
 *    取消集合中不存在于 tasks 的 id 直接忽略。
 *    tasks 按值传递：返回清理后的 list，调用者的原始 list 不改变。
 *    要求使用迭代器遍历和 list::erase；删除后接住 erase 返回的迭代器。
 *    用 unordered_set::find 判断是否取消，不用下标访问 list。
 *
 * B. fifo_order(tasks)
 *    用 std::queue<Task> 模拟先进先出，返回依次执行的任务 id。
 *    返回类型为 deque<int>，每完成一个任务就在结果尾部 push_back(id)。
 *
 * C. priority_order(tasks)
 *    用 std::priority_queue<Task, std::vector<Task>, TaskLowerPriority> 调度。
 *    priority 越大越先执行；相同 priority 时，id 越小越先执行。
 *    比较器已经给出，按顺序取 top/pop 并将 id 追加到 deque<int>。
 *
 * B/C 接受任意合法任务列表；需要取消任务时，先调用 A，再把返回值传给 B/C。
 * 所有函数都不能改变调用者传入的容器；空任务列表返回空容器。
 *
 * 示例：tasks={{1,2},{2,5},{3,5},{4,1}}，取消 id=2 后剩余 1、3、4。
 *       FIFO 顺序为 {1,3,4}；优先级顺序为 {3,1,4}。
 *
 * 目标复杂度：A 平均 O(n)，B 为 O(n)，C 为 O(n log n)，n 为任务数。
 * queue/priority_queue 访问元素前判断 empty，pop() 不返回元素。
 */
std::list<Task> remove_cancelled(
    std::list<Task> tasks, const std::unordered_set<int>& cancelled_ids);
std::deque<int> fifo_order(const std::list<Task>& tasks);
std::deque<int> priority_order(const std::list<Task>& tasks);

}  // namespace homework

