#include "exercise05_tasks.hpp"

#include <gtest/gtest.h>

#include <limits>
#include <utility>
#include <vector>

namespace homework {
namespace {

// 不要求学生为 Task 重载 operator==；测试辅助函数同时检查 id 和 priority。
std::vector<std::pair<int, int>> task_values(const std::list<Task>& tasks) {
    std::vector<std::pair<int, int>> result;
    for (const auto& task : tasks) {
        result.emplace_back(task.id, task.priority);
    }
    return result;
}

}  // namespace

TEST(Ex05Tasks, RemovesCancelledTasksAndPreservesOtherFields) {
    const auto result = remove_cancelled({{1, 2}, {2, 5}, {3, 5}, {4, 1}}, {2, 99});
    EXPECT_EQ(task_values(result),
              (std::vector<std::pair<int, int>>{{1, 2}, {3, 5}, {4, 1}}));
}

TEST(Ex05Tasks, SafelyRemovesConsecutiveFirstAndLastElements) {
    const auto result = remove_cancelled(
        {{1, 4}, {2, 3}, {3, 2}, {4, 1}, {5, 0}}, {1, 2, 4, 5});
    EXPECT_EQ(task_values(result), (std::vector<std::pair<int, int>>{{3, 2}}));
}

TEST(Ex05Tasks, HandlesEmptyListAndCancellingEverything) {
    EXPECT_TRUE(remove_cancelled({}, {1}).empty());
    EXPECT_TRUE(remove_cancelled({{1, 2}, {2, 3}}, {1, 2}).empty());
}

TEST(Ex05Tasks, EmptyOrUnknownCancellationSetKeepsAllTasks) {
    const std::list<Task> tasks{{3, -1}, {1, 0}, {2, 5}};
    EXPECT_EQ(task_values(remove_cancelled(tasks, {})), task_values(tasks));
    EXPECT_EQ(task_values(remove_cancelled(tasks, {99})), task_values(tasks));
}

TEST(Ex05Tasks, CancellationDoesNotModifyCallerInput) {
    const std::list<Task> tasks{{1, 2}, {2, 5}};
    const std::unordered_set<int> cancelled{1};
    const auto result = remove_cancelled(tasks, cancelled);
    EXPECT_EQ(task_values(tasks), (std::vector<std::pair<int, int>>{{1, 2}, {2, 5}}));
    EXPECT_EQ(cancelled, (std::unordered_set<int>{1}));
    EXPECT_EQ(task_values(result), (std::vector<std::pair<int, int>>{{2, 5}}));
}

TEST(Ex05Tasks, FifoFollowsArrivalOrderRegardlessOfPriority) {
    const std::list<Task> tasks{{4, 1}, {2, 9}, {8, -1}};
    EXPECT_EQ(fifo_order(tasks), (std::deque<int>{4, 2, 8}));
    EXPECT_EQ(task_values(tasks),
              (std::vector<std::pair<int, int>>{{4, 1}, {2, 9}, {8, -1}}));
}

TEST(Ex05Tasks, FifoHandlesEmptyAndSingleTask) {
    EXPECT_TRUE(fifo_order({}).empty());
    EXPECT_EQ(fifo_order({{7, -2}}), (std::deque<int>{7}));
}

TEST(Ex05Tasks, PriorityUsesDescendingPriorityAndAscendingId) {
    const std::list<Task> tasks{{5, 2}, {3, 5}, {1, 5}, {2, 0}};
    EXPECT_EQ(priority_order(tasks), (std::deque<int>{1, 3, 5, 2}));
    EXPECT_EQ(task_values(tasks),
              (std::vector<std::pair<int, int>>{{5, 2}, {3, 5}, {1, 5}, {2, 0}}));
}

TEST(Ex05Tasks, AllEqualPrioritiesUseIdOrder) {
    EXPECT_EQ(priority_order({{9, 1}, {3, 1}, {7, 1}}), (std::deque<int>{3, 7, 9}));
}

TEST(Ex05Tasks, PrioritySupportsNegativeAndExtremePriorities) {
    EXPECT_EQ(priority_order({{1, std::numeric_limits<int>::min()},
                              {2, -1}, {3, 0},
                              {4, std::numeric_limits<int>::max()}}),
              (std::deque<int>{4, 3, 2, 1}));
}

TEST(Ex05Tasks, PriorityHandlesEmptyAndSingleTask) {
    EXPECT_TRUE(priority_order({}).empty());
    EXPECT_EQ(priority_order({{7, -2}}), (std::deque<int>{7}));
}

TEST(Ex05Tasks, CancellationAndBothSchedulingModesWorkTogether) {
    const auto remaining = remove_cancelled({{1, 2}, {2, 5}, {3, 5}, {4, 1}}, {2});
    EXPECT_EQ(fifo_order(remaining), (std::deque<int>{1, 3, 4}));
    EXPECT_EQ(priority_order(remaining), (std::deque<int>{3, 1, 4}));
    EXPECT_EQ(task_values(remaining),
              (std::vector<std::pair<int, int>>{{1, 2}, {3, 5}, {4, 1}}));
}

}  // namespace homework
