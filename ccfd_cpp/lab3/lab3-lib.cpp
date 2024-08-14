#include "lab3-lib.hpp"

FigureInterface::FigureInterface() 
{
    std::cout << "FigureInterface CONSTRUCTOR" << std::endl;
}

FigureInterface::~FigureInterface() 
{
    std::cout << "FigureInterface DESTRUCTOR" << std::endl;
}

Figure::Figure(double _area): area{_area} 
{
    std::cout << "Figure CONSTRUCTOR" << std::endl;
}

double Figure::getArea() const 
{
    return area;
}

void Figure::setArea(double _area) 
{
    area = _area;
}

Circle::Circle(double _radius) : Figure{M_PI * _radius * _radius} 
{
    std::cout << "Circle CONSTRUCTOR" << std::endl;
}
// {
//     area = M_PI * _radius *_radius;

// }

Square::Square(double _edge) : Figure{_edge * _edge} 
{
    std::cout << "Square CONSTRUCTOR" << std::endl;
}
// {
//     area = _edge * _edge;
// }

void Figure::id() const
{
    std::cout << "Figure with area: " << area << std::endl;
}

void Circle::id() const
{
    std::cout << "Circle with area: " << area << std::endl;
}

void Square::id() const
{
    std::cout << "Square with area: " << area << std::endl;
}

void id(const Figure& fig)
{
    fig.id();
}

Figure::~Figure()
{
    std::cout << "Figure DESTRUCTOR" << std::endl;
}

Square::~Square()
{
    std::cout << "Square DESTRUCTOR" << std::endl;
}

Circle::~Circle()
{
    std::cout << "Circle DESTRUCTOR" << std::endl;
}

FigureVector::FigureVector(): counter(0) {}

FigureVector::~FigureVector()
{
    for(int i=0; i<counter; i++)
    {
        delete content[i];
    }
}

Figure* FigureVector::operator[](size_t num)
{
    if(num < counter)
    {
        return content[num];
    }
    return nullptr;
}

void FigureVector::push(Figure* fig)
{
    content[counter] = fig;
    counter++;
}

void FigureVector::pop()
{
    counter--;
    delete content[counter];
}

Figure* FigureFabric::operator()(const std::string& name, double value)
{
    if(name == "square")
    {
        return new Square{value};
    }
    else if(name == "circle")
    {
        return new Circle{value};
    }
    else
    {
        return nullptr;
    }
}

void FigureVector::idAll()
{
    for(int i=0; i<counter; i++)
    {
        content[i]->id();
    }
}

void Square::accept(FigureVisitatorBase& visitator)
{
    visitator.visit(*this);
}

void Circle::accept(FigureVisitatorBase& visitator)
{
    visitator.visit(*this);
}

void FigureVector::visitAll(FigureVisitatorBase& visitator)
{
    for(int i=0; i<counter; i++)
    {
        content[i]->accept(visitator);
    }
}

void PrintingVisitator::visit(Square&)
{
    std::cout << "Printing Square" << std::endl;
}

void PrintingVisitator::visit(Circle&)
{
    std::cout << "Printing Circle" << std::endl;
}