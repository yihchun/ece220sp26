/* position and order of local variables with inheritence */

#include <iostream>

class Shape {
public:
    Shape() { name = "default";
        std::cout << "constructing Shape " << this << std::endl;
        std::cout << "unused lives here: " << &unused << std::endl;}
    virtual ~Shape() {
        std::cout << "destructing Shape " << this << std::endl;}
    virtual float area() const {
        std::cout << "Don't know how to area of Shape " << this << std::endl;
        return 0;}
    virtual void not_overridden() const {
        std::cout << "Shape::not_overriden()\n";
    }
        
private:
    std::string name;
    int unused;
};

class Possessor_of_Right_Angles {
public:
    virtual int how_many() const {
        std::cout << "At least one, or you're an imposter\n";
        return 1;
    }
};
    
class Rectangle : public Shape, public Possessor_of_Right_Angles {
public:
    Rectangle() { h=w=0;
        std::cout << "constructing Rectangle " << this << std::endl;
        std::cout << "h lives here: " << &h << std::endl;}
    ~Rectangle() {
        std::cout << "destructing Rectangle " << this << std::endl;}
    float area() const {
        std::cout << "In Rect::area() " << this << std::endl;
        return h*w;}
    int how_many() const {
        std::cout << "how many at " << this << std::endl; return 4; }
private:
    float h,w;
};

std::string hello = "Hello world\n";

int main() {
    Rectangle *r = new Rectangle();
    Shape *s = r;
    Possessor_of_Right_Angles z;
    Possessor_of_Right_Angles *p;
    int x;
    std::cin >> x;
    if (x == 0) { p = &z; }
    else { p = r; }
    
    std::cout << p << std::endl;
    std::cout << s << std::endl;
    std::cout << r << std::endl;
    p->how_many();
    s->not_overridden();
    delete s;
}
