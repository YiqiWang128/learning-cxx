#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16];
    int cached; // 最早的尚未被计算器的位置索引
};

/*
// TODO: 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {

    for (; false; ++cached) {
        cache[cached] = cache[cached - 1] + cache[cached - 2];
    }
    return cache.cache[i];
}
*/
// TODO: 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    // 如果请求的斐波那契数已经在缓存中，直接返回
    if (i < cache.cached) {
        return cache.cache[i];
    }

    if (cache.cached < 2) {
        cache.cache[0] = 0;
        cache.cache[1] = 1;
        cache.cached = 2;
    }

    // 否则，计算并缓存从 cache.cached 到 i 的斐波那契数
    for (int j = cache.cached; j <= i; ++j) {
        if (j == 0) {
            cache.cache[j] = 0;
        } else if (j == 1) {
            cache.cache[j] = 1;
        } else {
            cache.cache[j] = cache.cache[j - 1] + cache.cache[j - 2];
        }
    }

    // 更新缓存中已经计算过的斐波那契数的个数
    cache.cached = i + 1;

    // 返回请求的斐波那契数
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // NOTICE: C/C++ 中，读取未初始化的变量（包括结构体变量）是未定义行为
    // READ: 初始化的各种写法 <https://zh.cppreference.com/w/cpp/language/initialization>
    FibonacciCache fib{};
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
