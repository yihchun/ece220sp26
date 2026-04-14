#include <iostream>

template <class T>
T sum(T a, T b) {
    return a+b;
}

int main() {
    std::cout << sum(2,3) << std::endl;
    std::cout << sum(2.7,3.1) << std::endl;
    return 0;
}
    
