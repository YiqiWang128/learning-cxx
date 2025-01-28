#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // 构造函数：初始化缓存
    Fibonacci() {
        // 假设 cache[0] = 0, cache[1] = 1
        cache[0] = 0;
        cache[1] = 1;
        cached = 2;  // 目前缓存了前两个数
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        
        /*
        for (; false; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
        */

        if (i < cached) {
            return cache[i];
        }

        // 否则，计算并缓存从 cached 到 i 的斐波那契数
        for (int j = cached; j <= i; ++j) {
            if (j == 0) {
                cache[j] = 0;
            } else if (j == 1) {
                cache[j] = 1;
            } else {
                cache[j] = cache[j - 1] + cache[j - 2];
            }
        }

        // 更新缓存中已经计算过的斐波那契数的个数
        cached = i + 1;

        // 返回请求的斐波那契数
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
