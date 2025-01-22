#include <iostream>
using namespace std;

int maxnum(int n)
{
    int a, b;
    if (n == 00)
        return 0;
    else
    {
        a = n % 10;
        b = maxnum(n / 10);
        if (a >  b)
            return a;
        else
            return b;

    }
}

int main()
{
    int n;
    cout << "Enter number N<2^31" << endl;
    cin >> n;
    cout << maxnum(n) << endl;
}