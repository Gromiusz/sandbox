#include <iostream>
#include <vector>
#include <memory>

class Element
{
public:
    virtual double getSize() = 0;
    virtual void add(std::unique_ptr<Element> el) = 0;
    virtual ~Element() = default;
};

class Leaf : public Element
{
    double area;
public:
    Leaf(const double& ar) : area(ar) {}
    double getSize() override { return area; } 
};

class Branch : public Element // Composite
{
    double length;
    std::vector<std::unique_ptr<Element>> vector;

public:
    Branch(const double& len) : length(len) {}
    double getSize() override { return length; }
    void add(std::unique_ptr<Element> el) override {
        vector.push_back(std::move(el));
    }

};

int main()
{
    std::unique_ptr<Branch> root = std::make_unique<Branch>(5);
    std::unique_ptr<Branch> branch_1 = std::make_unique<Branch>(2);
    std::unique_ptr<Branch> branch_2 = std::make_unique<Branch>(1);

    root->add(std::move(branch_1));
    root->add(std::move(branch_2));
}