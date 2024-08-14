#include <iostream>
#include <cmath>

class Vector
{
    size_t capacity;
    size_t size;
    double *content;

public:
    Vector(size_t n);
    ~Vector();

    size_t get_size();
    size_t get_capacity();
    void resize(size_t new_size);
    void print();

    double &operator[](unsigned int element);

    Vector(const Vector &ori);
    Vector(Vector &&ori);
    Vector &operator=(const Vector &ori);
    Vector &operator=(Vector &&ori);
};