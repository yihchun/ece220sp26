#include <iostream>

class A {
    int x;
public:
    A() { x = 0; }
    A(int v) { x = v; }
    int operator+(int a) const { return x+a; }
};

class B : public A {
public:
    B() : A() {}
    B(int v) : A(v) {}
    int operator+(int a) const { return 0; }
};

int main() {
    B x(3);
    A &y = x;
    std::cout << x+3 << std::endl; /* todo: why does this inherit +? */
    std::cout << y+3 << std::endl;
}
