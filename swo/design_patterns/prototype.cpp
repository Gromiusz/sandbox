#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Shape {
public:
    virtual std::shared_ptr<Shape> clone() = 0;
    virtual void draw() = 0;     
    virtual ~Shape() {}
};


class Circle : public Shape {
private:
    int radius;
public:
    Circle(int r) : radius(r) {}
    std::shared_ptr<Shape> clone() {
        return std::make_shared<Circle>(*this);
    }
    void draw() override {
        cout << "Drawing a circle with radius: " << radius << endl;
    }
};

class Rectangle : public Shape {
private:
    int width, height;
public:
    std::shared_ptr<Shape> clone() {
        return std::make_shared<Rectangle>(*this);
    }
    void draw() override {
        cout << "Drawing a rectangle with width: " << width << ", height: " << height << endl;
    }
};

int main()
{
    std::shared_ptr<Shape> circ = make_shared<Circle>(4);
    std::shared_ptr<Shape> circ_copy = circ->clone();
    circ_copy->draw();


}