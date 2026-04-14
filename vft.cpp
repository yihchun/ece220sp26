#include <iostream>

class Foo {
public:
    virtual void bar() const { std::cout << "I'm a Foo" << std::endl; }
};

class Baz {
public:
    virtual void hello() const { std::cout << "I'm a Baz" << std::endl; }
};

class Bar : public Foo, public Baz {
public:
    void bar() const { std::cout << "I'm a Bar\n"; }
    void hello() const { std::cout << "I'm a Bar, not a Baz\n"; }
};

int main() {
    Bar b;
    Foo *f = &b;
    Baz *z = &b;
    Foo x;
    z->hello();
    return 0;
}
