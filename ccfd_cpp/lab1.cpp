#include <iostream>
#include <cmath>

class Informer
{
public:
    Informer() {std::cout << "Informer CONSTRUCTOR" << std::endl;}
    ~Informer() {std::cout << "Informer DESTRUCTOR" << std::endl;}
};

class Wektor2D
{
    double x;
    double y;
    Informer informer;
    static int num_vec;
    Wektor2D(double a, double b): x{a}, y{b} {
        num_vec++;
        std::cout << "Vector CONSTRUCTOR" << std::endl;
        print();
        std::cout << std::endl;
    }

public:
    ~Wektor2D() {
        num_vec--;
        std::cout << "Vector DESTRUCTOR" << std::endl;
        print();
        std::cout << std::endl;
    }

    void setX(double a) {x = a;}
    void setY(double a) {y = a;}
    double getX() const {return x;}
    double getY() const {return y;}
    double norm() {return std::sqrt(x*x + y*y);}
    void print() {std::cout << "Vector coordinates   x: " << x << "  y: " << y << std::endl;}

    static int population() {return num_vec;}
    static Wektor2D kart(double a, double b) {return Wektor2D{a, b};}
    static Wektor2D bieg(double radius, double theta) {return Wektor2D{radius * cos(theta), radius * sin(theta)};}

    friend Wektor2D operator*(const Wektor2D& vec1, const Wektor2D& vec2);
    friend Wektor2D operator+(const Wektor2D& vec1, const Wektor2D& vec2);
    friend std::ostream& operator<<(std::ostream& os, const Wektor2D& vec);
};

Wektor2D operator+(const Wektor2D& vec1, const Wektor2D& vec2)
{
    return Wektor2D::kart(vec1.x + vec2.x, vec1.y + vec2.y);
}

Wektor2D operator*(const Wektor2D& vec1, const Wektor2D& vec2)
{
    return Wektor2D::kart(vec1.x * vec2.x, vec1.y * vec2.y);
}

std::ostream& operator<<(std::ostream& os, const Wektor2D& vec)
{
    os << "Vector coordinates   x: " << vec.x << "  y: " << vec.y << std::endl;
    return os;
}

int Wektor2D::num_vec = 0;

int main()
{
    {
        Wektor2D vector1 = Wektor2D::kart(3.2, 5.1);
        Wektor2D vector2 = Wektor2D::bieg(2, 7);

        Wektor2D vec3 = vector1 + vector2;
        vec3.print();
        std::cout << vec3 << vector1 << vector2;
    }
    std::cout << Wektor2D::population();
    std::cout << std::endl;
}