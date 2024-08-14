#include "lab2.hpp"

Vector::Vector(size_t n) : capacity{n}, size{n}
{
    content = new double[n];
    for (int i = 0; i < size; i++)
    {
        content[i] = 0;
    }
}

Vector::~Vector()
{
    delete[] content;
}

size_t Vector::get_size()
{
    return size;
}

size_t Vector::get_capacity()
{
    return capacity;
}

void Vector::resize(size_t new_size)
{
    if (new_size <= capacity && new_size <= size)
    {
        size = new_size;
    }
    else if (new_size <= capacity && new_size > size)
    {
        for (size_t i = size; i < new_size; i++)
        {
            content[i] = 0;
        }
        size = new_size;
    }
    else
    {
        double *new_content = new double[new_size];
        for (size_t i = 0; i < size; i++)
        {
            new_content[i] = content[i];
        }
        for (size_t i = size; i < new_size; i++)
        {
            new_content[i] = 0;
        }
        size = new_size;
        capacity = size;
        delete[] content;
        content = new_content;
    }
}

void Vector::print()
{
    std::cout << "Vector with size " << size << " content:   ";
    for (int i = 0; i < size; i++)
    {
        std::cout << content[i] << " ";
    }
    std::cout << std::endl;
}

double &Vector::operator[](unsigned int element)
{
    if (element > size)
    {
        resize(element + 1);
    }
    return content[element];
}

Vector::Vector(const Vector &ori) : capacity{ori.capacity}, size{ori.size}
{
    content = new double[capacity];
    resize(size);
    for (int i = 0; i < ori.size; i++)
    {
        content[i] = ori.content[i];
    }
}

Vector::Vector(Vector &&ori) : capacity{ori.capacity}, size{ori.size}
{
    content = ori.content;
    ori.content = nullptr;
}

Vector &Vector::operator=(const Vector &ori)
{
    if(&ori != this)
    {
        capacity = ori.capacity;
        size = ori.size;
        delete[] content;
        content = new double[capacity];
        resize(size);
        for (int i = 0; i < ori.size; i++)
        {
            content[i] = ori.content[i];
        }
    }
    return *this;
}

Vector &Vector::operator=(Vector &&ori)
{
    if(&ori != this)
    {
        capacity = ori.capacity;
        size = ori.size;
        delete[] content;
        content = ori.content;
        ori.content = nullptr;
    }
    return *this;
}

