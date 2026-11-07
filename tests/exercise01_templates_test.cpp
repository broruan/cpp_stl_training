#include "exercise01_templates.hpp"

#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>

namespace homework {

// 编译期检查接口：get() 应可用于 const 对象，并返回 const 引用。
static_assert(std::is_same_v<decltype(std::declval<const Box<int>&>().get()),
                             const int&>);

TEST(Ex01Templates, MaxHandlesIntegersAndEqualValues) {
    EXPECT_EQ(max_value(3, 8), 8);
    EXPECT_EQ(max_value(9, 2), 9);
    EXPECT_EQ(max_value(-3, -8), -3);
    EXPECT_EQ(max_value(5, 5), 5);
}

TEST(Ex01Templates, MaxHandlesDoublesAndExplicitType) {
    EXPECT_DOUBLE_EQ(max_value(2.5, 1.8), 2.5);
    EXPECT_DOUBLE_EQ(max_value<double>(3, 2.5), 3.0);
}

TEST(Ex01Templates, MaxHandlesCharactersAndStrings) {
    EXPECT_EQ(max_value('a', 'z'), 'z');
    EXPECT_EQ(max_value(std::string("apple"), std::string("pear")), "pear");
}

TEST(Ex01Templates, BoxReadsAndUpdatesInteger) {
    Box<int> box(10);
    EXPECT_EQ(box.get(), 10);
    box.set(20);
    EXPECT_EQ(box.get(), 20);
}

TEST(Ex01Templates, BoxSupportsStringsAndConstAccess) {
    Box<std::string> box("hello");
    const auto& read_only = box;
    EXPECT_EQ(read_only.get(), "hello");
    box.set("world");
    EXPECT_EQ(read_only.get(), "world");
    box.set("");
    EXPECT_TRUE(box.get().empty());
}

TEST(Ex01Templates, BoxesKeepIndependentState) {
    Box<int> first(1);
    Box<int> second(2);
    first.set(100);
    EXPECT_EQ(first.get(), 100);
    EXPECT_EQ(second.get(), 2);
}

TEST(Ex01Templates, BoxGetReturnsReferenceToStoredValue) {
    Box<int> box(7);
    const int& value = box.get();
    box.set(9);
    EXPECT_EQ(value, 9);
}

TEST(Ex01Templates, SumArrayHandlesIntegersAndNegatives) {
    EXPECT_EQ(sum_array(std::array<int, 4>{1, -2, 3, 4}), 6);
    EXPECT_EQ(sum_array(std::array<int, 1>{-5}), -5);
}

TEST(Ex01Templates, SumArrayHandlesDoubles) {
    EXPECT_DOUBLE_EQ(sum_array(std::array<double, 3>{1.5, 2.0, 0.5}), 4.0);
}

TEST(Ex01Templates, SumArrayHandlesZeroLength) {
    EXPECT_EQ(sum_array(std::array<int, 0>{}), 0);
    EXPECT_DOUBLE_EQ(sum_array(std::array<double, 0>{}), 0.0);
}

}  // namespace homework

