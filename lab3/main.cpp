#include<iostream>
#include<cmath>
using namespace std;


struct Para {
    private:
        int a, b, angle, height, per;
        float area;
        
    public:
        void NumsOfPara()
        {
            cout << "enter number a of para" << endl;
            cin >> a;
            cout << "enter number b of para" << endl;
            cin >> b;
            cout << "enter angle between a and b (if u don`t have enter 0)" << endl;
            cin >> angle;
            cout << "enter height of para (if u don`t have enter 0)" << endl;
            cin >> angle;
        }

        void Area()
        {
            if (height != 0) {
                area = a * height;
                cout << "area is " << area << endl;
            }
            else if (angle != 0)
                {
                    float sinangle = sin(angle);
                    area = (a * b * sinangle) / 2;

                    cout << "area is " << area << endl;
                }
            else 
                cout << "No data" << endl;
        }
        
        void Per() {
            cout << "per is " << (a + b) * 2 << endl;
        }
};

int main()
{
    
}