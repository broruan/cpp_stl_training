# C++ 模板与 STL 入门作业

基于培训文档整理，共 **5 道题**，从单个模板工具逐步过渡到多个容器的简单组合。使用 **C++17 + GoogleTest + CMake**。只需要补全 TODO，不要求手写链表、哈希表、堆，也不涉及并发。

## 题目安排

| 题号 | 题目 | 难度 | 主要知识点 | 建议分值 |
| --- | --- | --- | --- | --- |
| 1 | 三个小型模板工具 | 入门 | 函数模板、类模板、类型推导、非类型模板参数、`array` | 15 |
| 2 | 整理一组数字 | 基础 | `vector`、迭代器、删除、排序、去重、统计、求和、二分查找 | 20 |
| 3 | 判断括号是否匹配 | 基础应用 | `string`、`stack`、后进先出、边界判断 | 20 |
| 4 | 词频统计与查询 | 容器组合 | `unordered_map`、`set`、`map`、只读查询、有序与无序 | 20 |
| 5 | 简单任务调度 | 小型综合 | `list`、安全删除、`unordered_set`、`queue`、`priority_queue`、`deque` | 25 |

每题的 **完整题意、输入输出、示例、边界条件和提示都写在对应头文件的中文注释中**。第 5 题的优先队列比较器已提供，只需实现基础的容器操作。

文档中的模板特化、可变参数模板和移动语义保留为阅读知识，本次不要求编写这些进阶内容。`reserve/resize`、迭代器失效和 `map[key]` 的副作用在题目注释中作了提醒。

## 文件与作答位置

```text
.
├── CMakeLists.txt
├── README.md
├── include/
│   ├── exercise01_templates.hpp  # 第 1 题：题意和模板实现 TODO
│   ├── exercise02_numbers.hpp    # 第 2 题：题意、结果结构和接口
│   ├── exercise03_brackets.hpp   # 第 3 题：题意和接口
│   ├── exercise04_words.hpp      # 第 4 题：题意、统计结构和接口
│   └── exercise05_tasks.hpp      # 第 5 题：题意、任务结构、比较器和接口
├── src/
│   ├── exercise02_numbers.cpp    # 第 2 题实现 TODO
│   ├── exercise03_brackets.cpp   # 第 3 题实现 TODO
│   ├── exercise04_words.cpp      # 第 4 题实现 TODO
│   └── exercise05_tasks.cpp      # 第 5 题实现 TODO
└── tests/
    ├── exercise01_templates_test.cpp
    ├── exercise02_numbers_test.cpp
    ├── exercise03_brackets_test.cpp
    ├── exercise04_words_test.cpp
    └── exercise05_tasks_test.cpp
```

只需修改 `include/exercise01_templates.hpp` 和 `src/` 下的四个文件。保留既有函数名、参数和返回类型；可以增加需要的头文件或辅助函数。无需编写 `main()`，测试入口由 `GTest::gtest_main` 提供。

## 构建和运行

需要支持 C++17 的编译器、CMake 3.20 或更新版本，以及对应的构建工具。第一次配置需要联网下载固定提交版本的 GoogleTest，之后在同一构建目录中可以重复构建。

### 通用命令 / Visual Studio 开发者终端

在项目根目录运行：

```sh
cmake -S . -B build
cmake --build build --config Debug --parallel 4
ctest --test-dir build -C Debug --output-on-failure
```

如果使用 Ninja 和 GCC，且 `cmake`、`ninja`、`g++` 都在 PATH 中：

```sh
cmake -S . -B build-ninja -G Ninja -DCMAKE_CXX_COMPILER=g++
cmake --build build-ninja --parallel 4
ctest --test-dir build-ninja --output-on-failure
```

切换编译器或生成器时使用新的构建目录。Windows 使用 MinGW 时，也需将它的 `bin` 目录放在 PATH 中，以便运行测试程序。

### 只运行某一题

以第 1 题、第 5 题为例；使用其他构建目录时相应替换 `build`：

```sh
ctest --test-dir build -C Debug -R "^Ex01Templates\." --output-on-failure
ctest --test-dir build -C Debug -R "^Ex05Tasks\." --output-on-failure
```

也可以直接使用 GoogleTest 的过滤器。Ninja/Makefile 构建的 Windows 示例：

```powershell
.\build\homework_tests.exe --gtest_filter="Ex03Brackets.*"
```

Visual Studio 构建通常将程序放在 `build/Debug/homework_tests.exe`。优先用上面的 CTest 命令即可避开路径差异。

### 当前工作目录已准备的本机工具

本次在 `D:\28_training` 的 `.tools` 中准备了 CMake 和 Ninja，使用本机已有的 MinGW GCC；没有修改全局 PATH。留在此工作目录继续作答时，可以直接运行：

```powershell
& .\.tools\cmake\data\bin\cmake.exe --build build --parallel 4
& .\.tools\cmake\data\bin\ctest.exe --test-dir build -R "^Ex01Templates\." --output-on-failure
```

`.tools`、构建输出和内部验证文件不包含在发给学员的 ZIP 中。其他机器按前面的通用步骤准备工具。

## 如何理解测试结果

项目提供 **47 个 GoogleTest 测试用例**，分别为第 1～5 题的 10、9、8、8、12 个。测试覆盖正常数据、空输入、重复元素、边界查找、较大的累加结果、错误嵌套、只读查询、连续删除及同优先级任务排序。

初始框架能够编译，但 TODO 中统一抛出 `std::logic_error("TODO: ...")`，因此初次运行测试会失败。这是预期行为。实现函数时将对应的占位异常替换为自己的代码，逐题运行测试即可。初始构建中的 `unused parameter` 警告来自占位函数尚未使用参数，不影响编译。

测试检查可观察到的结果；是否使用题目指定的容器和算法、是否满足复杂度要求，还需要阅读代码确认。不要为使测试通过而修改测试或硬编码样例答案。

交付前已在 Windows + MinGW GCC 环境中验证：学生框架编译成功，47 个测试按预期报告 TODO；使用隔离的临时参考实现后，47/47 个测试通过。验证用实现不包含在学员 ZIP 中。

## 提交要求

提交完成后的第 1 题头文件和四个 `.cpp` 文件，也可以提交整个项目源码；不提交 `build/`、`.tools/` 等生成目录。保留注释，代码中简要说明不容易看懂的判断即可。

构建配置采用 [GoogleTest 官方 CMake 快速入门](https://google.github.io/googletest/quickstart-cmake.html) 中的 `FetchContent`、`GTest::gtest_main` 和 `gtest_discover_tests` 方式，并从源码构建 GoogleTest，保持与作业使用相同的编译器。
