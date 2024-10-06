class Klasa
{
    const double abc;
public:
    Klasa(double aaa) : abc(aaa) {}
    //Klasa() : abc(0) {}
    Klasa() : abc(0) {};
};

class DD : public Klasa
{

};

int main()
{
    DD kasldk;
}