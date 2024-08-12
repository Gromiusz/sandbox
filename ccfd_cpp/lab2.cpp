#include <iostream>
#include <cmath>

class Vector
{
    size_t capacity;
    size_t size;
    double* content;

public:
    
    Vector(size_t n): capacity{n}, size{n} {
        content = new double[n];
        for(int i=0; i<size; i++) {
            content[i] = 0;
        }
    }
    ~Vector() {
        delete[] content;
    }

    size_t get_size() {return size;}
    size_t get_capacity() {return capacity;}
    void resize(size_t new_size) {
        if(new_size <= capacity && new_size <= size) {
            size = new_size;
        }
        else if(new_size <= capacity && new_size > size) {
            for(size_t i=size; i<new_size; i++) {
                content[i] = 0;
            }
            size = new_size;
        }
        else {
            double* new_content = new double[new_size];
            for(size_t i = 0; i < size; i++) {
                new_content[i] = content[i];
            }
            for (size_t i = size; i < new_size; i++){
                new_content[i] = 0;
            }
            size = new_size;
            capacity = size;
            delete[] content;
            content = new_content;
        }
    }
    void print() {
        std::cout << "Vector with size " << size << " content:   ";
        for(int i=0; i<size; i++) {
            std::cout << content[i] << " ";
        }
        std::cout << std::endl;
    }

    double& operator[](unsigned int element) {
        if(element>size) {
            resize(element+1);
        }
        return content[element];
    }

};

int main() {
    Vector vec1{4};
    vec1.print();
    vec1[3] = 4;
    vec1.print();

    vec1.resize(10);
    vec1.print();

    vec1[0] = 42.;
    double a = vec1[0];
    a++;

    vec1[14] = 3.;
    vec1.print();

}