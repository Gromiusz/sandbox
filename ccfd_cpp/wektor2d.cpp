#include <cmath>
#include <iostream>

class Informer
{
public:
    Informer(){std::cout << "Informer CONSTRUCTOR\n";}
    ~Informer(){std::cout << "Informer DESTRUCTOR\n";}
};

class Wektor2D
{
    double x;
    double y;

    Informer informer;

public:
    void setX(double _x){x = _x;}
    void setY(double _y){y = _y;}

    double getX() const {return x;}
    double getY() const {return y;}

    Wektor2D() = default;

    Wektor2D(double a, double b): x{a}, y{b}
    {
        std::cout << "CONSTRUCTOR for" << std::endl;
        print();
    }

    ~Wektor2D()
    {
        std::cout << "DESTRUCTOR for" << std::endl;
        print();
    }

    double norm() {
        return std::sqrt(x*x + y*y);
    }

    void print() {
        
        std::cout << "Vector coordinates: " << std::endl;
        std::cout << "x: " << x << std::endl << "y: " << y << std::endl << std::endl;
    }

    
};

Wektor2D operator+(const Wektor2D& v1, const Wektor2D& v2)
{
    return Wektor2D{v1.getX() + v2.getX(), v1.getY() + v2.getY()};

}

int main()
{
    Wektor2D wektor{10, 20};
    Wektor2D wektor2{2.3, 1.2};

    std::cout << wektor.norm() << std::endl;
    wektor.print();
}