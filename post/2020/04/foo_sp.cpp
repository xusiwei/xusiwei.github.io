#include <stdio.h>
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

struct Foo {
    Foo(int n)
        : data(n)
    {
        printf("Foo_%p {data: %d} born!\n", this, data);
    }

    ~Foo()  { printf("Foo_%p {data: %d} die!\n", this, data); }

    int data;
};

int GetPriority(int n)
{
    static const int priorities[]{20, 21, 22};
    if (n < 0) {
        throw std::invalid_argument("n invalid: " + std::to_string(n));
    } else if (n > sizeof(priorities)/sizeof(priorities[0])) {
        throw std::out_of_range("n out of range: " + std::to_string(n));
    }
    return priorities[n];
}

void Process(const std::shared_ptr<Foo>& foo, int priority)
{
}

int main()
{
    std::shared_ptr<Foo> p0{new Foo(0)};

    try {
        std::shared_ptr<Foo> p1{new Foo(-1)};
        Process(p1, GetPriority(p1->data));
    } catch (std::exception& e) {
        std::cout << "exception raised:" << e.what() << std::endl;
    }

    try {
        Foo* p2 = new Foo(-2);
        Process(std::shared_ptr<Foo>(new Foo(-2)), GetPriority(p2->data));
    } catch (std::exception& e) {
        std::cout << "exception raised:" << e.what() << std::endl;
    }
    return 0;
}