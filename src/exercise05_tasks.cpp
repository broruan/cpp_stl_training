#include "exercise05_tasks.hpp"

#include <queue>
#include <stdexcept>
#include <vector>

namespace homework {

std::list<Task> remove_cancelled(
    std::list<Task> tasks, const std::unordered_set<int>& cancelled_ids) {
    // TODO：安全地删除已取消的任务，返回剩余 list。

}

std::deque<int> fifo_order(const std::list<Task>& tasks) {
    // TODO：先入队，再逐个取出，形成执行记录。

}

std::deque<int> priority_order(const std::list<Task>& tasks) {
    // TODO：使用已给出的比较器建立优先队列，形成执行记录。

}

}  // namespace homework
