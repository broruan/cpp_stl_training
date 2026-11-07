#pragma once

#include <array>
#include <cstddef>
#include <stdexcept>

namespace homework {

/*
 * 第 1 题：实现三个小型模板工具（入门）
 *
 * 知识点：函数模板、类型推导、显式模板实参、类模板、非类型模板参数、array。
 * 只修改本文件的 TODO。模板定义保留在 .hpp 中，便于编译器实例化。
 *
 * A. max_value(a, b)
 *    返回两个值中较大的值；相等时返回任意一个即可。
 *    T 必须支持 > 和复制；测试使用 int、double、char、std::string。
 *    示例：max_value(3, 8) == 8；max_value<double>(3, 2.5) == 3.0。
 *    提示：max_value(3, 2.5) 的类型推导会冲突，需要显式指定 double。
 *
 * B. Box<T>
 *    构造函数已给出。get() 返回内部值的 const 引用；set() 替换内部值。
 *    示例：Box<int> box(10); box.set(20); 此后 box.get() == 20。
 *    多个 Box 对象的状态必须相互独立，不使用全局变量或静态变量存值。
 *
 * C. sum_array(values)
 *    对 std::array<T, N> 的所有元素求和，返回 T。
 *    T 为本题使用的数值类型 int 或 double，保证结果在 T 的可表示范围内。
 *    N 可以为 0；此时返回 T{}（数值类型为 0）。
 *    示例：std::array<int, 3>{1, 2, 3} 的和是 6。
 *    提示：N 是编译期常量；用范围 for 和一个 T 类型的累加变量即可。
 *
 * 不要求实现模板特化或可变参数模板。
 */

template <typename T>
T max_value(const T& a, const T& b) {
    // TODO：用比较表达式返回结果。
    return a>b?a:b;
}

template <typename T>
class Box {
public:
    explicit Box(const T& value) : value_(value) {}

    const T& get() const {
        // TODO：返回 value_，不要返回局部变量的引用。
        return value_;
    }

    void set(const T& value) {
        // TODO：更新 value_。
        value_=value;
    }

private:
    T value_;
};

template <typename T, std::size_t N>
T sum_array(const std::array<T, N>& values) {
    // TODO：从 T{} 开始累加。
    T n{0};
    for(std::size_t i=0;i<values.size();++i){
        n += values[i];
    }
    
    return n;
}

}  // namespace homework

