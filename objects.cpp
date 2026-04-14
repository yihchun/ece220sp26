#include <iostream>
#include <math.h>

class Vec {
    friend std::ostream &operator<<(std::ostream &os, const Vec &a);
private:
    double x, y;
public:
    Vec() { x=y=0; }
    Vec(double x, double y) { this->x = x; this->y = y; }
    static Vec fromPolar(double r, double theta) {
        return Vec(r*cos(theta), r*sin(theta));}
    ~Vec() { std::cout << this << " is off to the abyss\n"; }
    Vec operator+(const Vec &other) const {
        return Vec(other.x+x, other.y+y);
    }
};

std::ostream &operator<<(std::ostream &os, const Vec &a) {
    os << a.x << "," << a.y;
    return os;
}

int main() {
    int x;
    int &y = x;
    y = 3;
    Vec a = Vec::fromPolar(2,3.14159/4);
    Vec b(1,2);
    Vec c = a+b;
    std::cout << c << std::endl;
}
