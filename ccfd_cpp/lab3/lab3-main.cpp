#include "lab3-lib.hpp"

int main()
{
    // Circle circle{3};
    // circle.id();
    // id(circle);
    // id(static_cast<Figure>(circle));
    //FigureInterface fig;
    FigureInterface* f = new Square{4};
    f->id();
    delete f;
    // std::cout << dynamic_cast<Square*>(f) << std::endl;
    // std::cout << dynamic_cast<Circle*>(f) << std::endl;

    FigureVector vec;
    vec.push(new Square{3});
    vec.push(new Circle{3});
    vec.push(new Circle{8});
    Figure* f1;
    f1 = vec[0];

    FigureFabric fabric;
    Figure* fsquare = fabric("square", 5);
    delete fsquare;

    PrintingVisitator printer;
    vec.visitAll(printer);
}