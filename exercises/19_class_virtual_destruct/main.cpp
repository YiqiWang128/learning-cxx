#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // TODO: 正确初始化静态字段
    //static int num_a = 0;
    static int num_a; // 类内声明

    A() {
        ++num_a;
        std::cout<<"construct A"<<std::endl;
    }
    // 必须改成虚析构函数
    virtual ~A() {
        --num_a;
        std::cout<<"destruct A"<<std::endl;
    }

    virtual char name() const {
        return 'A';
    }
};
int A::num_a = 0; // 类外初始化

struct B final : public A {
    // TODO: 正确初始化静态字段
    //static int num_b = 0;
    static int num_b; // 类内声明

    B() {
        ++num_b;
        std::cout<<"construct B"<<std::endl;
    }
    // 必须改成虚析构函数
    virtual ~B() {
        --num_b;
        std::cout<<"destruct B"<<std::endl;
    }

    char name() const final {
        return 'B';
    }
};
int B::num_b = 0; // 类外初始化


int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    std::cout<<"------------------"<<std::endl;

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    std::cout<<"------------------"<<std::endl;

    A *ab = new B;// 派生类指针可以随意转换为基类指针
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    std::cout<<"------------------"<<std::endl;

    // TODO: 基类指针无法随意转换为派生类指针，补全正确的转换语句
    //B &bb = *ab;
    B &bb = dynamic_cast<B&>(*ab);
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    std::cout<<"------------------"<<std::endl;

    // TODO: ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    delete ab;// 通过指针可以删除指向的对象，即使是多态对象
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    std::cout<<"------------------"<<std::endl;

    return 0;
}
