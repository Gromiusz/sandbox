#pragma once
#include <iostream>
#include <cmath>

class Square;
class Circle;

class FigureInterface
{
public:
    FigureInterface();
    virtual ~FigureInterface();
    virtual void id() const = 0;
};

class FigureVisitatorBase
{
public:
    virtual void visit(Square&) = 0;
    virtual void visit(Circle&) = 0;
};

class Figure : public FigureInterface
{
protected:
    double area;
    Figure(double _area);

public:
    virtual void accept(FigureVisitatorBase& visitator) = 0;
    virtual ~Figure();
    double getArea() const;
    void setArea(double _area);
    virtual void id() const;
};

class Square : public Figure
{
public:
    Square(double _edge);
    ~Square();
    void id() const override;
    void accept(FigureVisitatorBase& visitator);
};

class Circle : public Figure
{
public:
    Circle(double _edge);
    ~Circle();
    void id() const override;
    void accept(FigureVisitatorBase& visitator);
};

void id(const Figure& fig);

class FigureVector
{
    Figure* content[100];
    size_t counter;
public:
    FigureVector();
    ~FigureVector();
    Figure* operator[](size_t num);
    void push(Figure* fig);
    void pop();
    void idAll();
    void visitAll(FigureVisitatorBase&);
};

class FigureFabric
{
public:
    Figure* operator()(const std::string&, double);
};

class PrintingVisitator : public FigureVisitatorBase
{
public:
    void visit(Square&);
    void visit(Circle&);
};