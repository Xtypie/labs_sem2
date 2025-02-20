#include<iostream>
#include<cmath>
using namespace std;


class Para {
private:
    float a;    
    float b;    
    float h;  

public:
    
    Para(float a, float b, float h) : a(a), b(b), h(h) {}

    float Area()
    {
        return a * h;
    }

    float Per()
    {
        return 2 * (a + b);
    }

    void print() 
    {
        cout << "area is "<< Area() << endl;
        cout << "perimeter is " << Per() << endl;
    }

};

int main() 
{
    Para parallelogram(5, 4, 3);

    parallelogram.print();

}