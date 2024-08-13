#include "lab2.hpp"

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