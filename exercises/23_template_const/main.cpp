#include "../exercise.h"
#include <cstring>

// READ: 模板非类型实参 <https://zh.cppreference.com/w/cpp/language/template_parameters#%E6%A8%A1%E6%9D%BF%E9%9D%9E%E7%B1%BB%E5%9E%8B%E5%AE%9E%E5%8F%82>

/*
template<unsigned int N, class T>
struct Tensor {
    unsigned int shape[N];
    T *data;

    Tensor(unsigned int const shape_[N]) {
        unsigned int size = 1;
        // TODO: 填入正确的 shape 并计算 size
        data = new T[size];
        std::memset(data, 0, size * sizeof(T));
    }
    ~Tensor() {
        delete[] data;
    }

    // 为了保持简单，禁止复制和移动
    Tensor(Tensor const &) = delete;
    Tensor(Tensor &&) noexcept = delete;

    T &operator[](unsigned int const indices[N]) {
        return data[data_index(indices)];
    }
    T const &operator[](unsigned int const indices[N]) const {
        return data[data_index(indices)];
    }

private:
    unsigned int data_index(unsigned int const indices[N]) const {
        unsigned int index = 0;
        for (unsigned int i = 0; i < N; ++i) {
            ASSERT(indices[i] < shape[i], "Invalid index");
            // TODO: 计算 index
        }
        return index;
    }
};
*/


template<unsigned int N, class T>
struct Tensor {
    unsigned int shape[N];
    T *data;

    Tensor(unsigned int const shape_[N]) {
        unsigned int size = 1;
        for (unsigned int i = 0; i < N; ++i) {
            shape[i] = shape_[i];
            size *= shape[i];
        }
        data = new T[size];
        std::memset(data, 0, size * sizeof(T));
    }
    ~Tensor() {
        delete[] data;
    }

    // 为了保持简单，禁止复制和移动
    Tensor(Tensor const &) = delete;
    Tensor(Tensor &&) noexcept = delete;

    T &operator[](unsigned int const indices[N]) {
        return data[data_index(indices)];
    }
    T const &operator[](unsigned int const indices[N]) const {
        return data[data_index(indices)];
    }

private:
    unsigned int data_index(unsigned int const indices[N]) const {
        unsigned int index = 0;
        for (unsigned int i = 0; i < N; ++i) {
            ASSERT(indices[i] < shape[i], "Invalid index");
            unsigned int product = 1;
            for (unsigned int j = i + 1; j < N; ++j) {
                product *= shape[j];
            }
            index += indices[i] * product;
        }
        return index;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{2, 3, 4, 5}; // 张量形状为 [2,3,4,5]，总元素数 = 2*3*4*5 = 120
        auto tensor = Tensor<4, int>(shape); // 创建四维张量

        // 测试点 1：索引 [0,0,0,0] (索引从0开始)
        unsigned int i0[]{0, 0, 0, 0};
        tensor[i0] = 1;
        ASSERT(tensor[i0] == 1, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1, "tensor[i0] should be 1");

        // 测试点 2：索引 [1,2,3,4] (索引从0开始)
        unsigned int i1[]{1, 2, 3, 4};
        tensor[i1] = 2; // 写入最后一个元素（线性索引 119）
        ASSERT(tensor[i1] == 2, "tensor[i1] should be 2");
        ASSERT(tensor.data[119] == 2, "tensor[i1] should be 2");
    }
    {
        unsigned int shape[]{7, 8, 128}; // 张量形状为 [7,8,128]，总元素数 = 7*8*128 = 7168
        auto tensor = Tensor<3, float>(shape); // 创建三维张量

        // 测试点 1：索引 [0,0,0]
        unsigned int i0[]{0, 0, 0}; 
        tensor[i0] = 1.f;
        ASSERT(tensor[i0] == 1.f, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1.f, "tensor[i0] should be 1");

        // 测试点 2：索引 [3,4,99]
        unsigned int i1[]{3, 4, 99};
        tensor[i1] = 2.f;
        ASSERT(tensor[i1] == 2.f, "tensor[i1] should be 2");
        ASSERT(tensor.data[3683] == 2.f, "tensor[i1] should be 2");
    }
    return 0;
}
