#include <iostream>
#include<fstream>
#include<thread>
#include<time.h>
using namespace std;


int maxnum(int n)
{
    int a, b;
    if (n == 0)
        return 0;
    a = n % 10;
    b = maxnum(n / 10);
    if (a > b)
        return a;
    return b;
}

void QuickSort(int a, int b, int* arr)
{
    if (a >= b)
        return;
    int m = arr[(a+b)/2];
    // presort
    int l = a;
    int r = b;
    while(l <= r)
    {
        while (arr[l] < m) l++;
        while (arr[r] > m) r++;
        if (l <= r)
        {
            swap(arr[l], arr[r]);
            l++;
            r--;
        }

    }
    QuickSort(a, r, arr);
    QuickSort(l, b, arr);
}

// void QuickSort(int a[], int left, int right) {
//     if (left > right) return;
//     int p= a[(left+right)/2];
//     int i = left;
//     int j =right;
//     while (i<=j) {
//         while (a[i] < p) i++;
//         while (a[j] > p) j--;
//         if (i<=j) {
//             int tmp= a[i];
//             a[i] = a[j];
//             a[j]= tmp;
//             i++;
//             j--;
//         }
//     }
//     QuickSort(a,left,j);
//     QuickSort(a,i,right);
// }

void labirint(int i, int j, int steps, int n, int m, char field[100][100], int table[100][100])
{
    if (steps >= table[i][j])
        return;

    table[i][j] = steps;

    if (i + 1 < n && field[i + 1][j] != '#')
        labirint(i + 1, j, steps + 1, n, m, field, table);
    if (i - 1 >= 0 && field[i - 1][j] != '#')
        labirint(i - 1, j, steps + 1, n, m, field, table);
    if (j + 1 < m && field[i][j + 1] != '#')
        labirint(i, j + 1, steps + 1, n, m, field, table);
    if (j - 1 >= 0 && field[i][j - 1] != '#')
        labirint(i, j - 1, steps + 1, n, m, field, table);

    if (i+1 < n && j+1<m && field[i+1][j+1] != '#')
        labirint(i+1, j+1, steps+1, n, m, field, table);
    if (i+1 < n && j-1 >= 0 && field[i+1][j-1] != '#')
        labirint(i+1, j-1, steps+1, n, m, field, table);
    if (i-1 >= 0 && j+1 < m && field[i-1][j+1] != '#')
        labirint(i-1, j+1, steps+1, n, m, field, table);
    if (i-1 >= 0 && j-1 >= 0 && field[i-1][j-1] != '#')
        labirint(i-1, j-1, steps+1, n, m, field, table);
}

const int a = 10;
int arr[a] = {2, 3, 1, 6, 4};

int main()
{
    // Task 1
    int n1;
    cout << "Enter number N<2^31" << endl;
    cin >> n1;
    cout << maxnum(n1) << endl;

    //Task 2
    const int a = 10;

    int arr[a] = {2, 3, 1, 6, 4, 9, 5};
    QuickSort(0, a - 1, arr);
    
    for (int i = 0; i < a; i++)
        cout << arr[i] << " ";
    cout << endl;

    // Task 3
    char field[100][100];
    int table[100][100];
    

    int is, js, ie, je;
    ifstream in("input.txt");
    int n, m;
    in >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            table[i][j] = INT_MAX;
            in >> field[i][j];
            if (field[i][j] == 'S')
            {
                is = i;
                js = j;
            }
            else if (field[i][j] == 'E')
            {
                ie = i;
                je = j;
            }
        }
    }

    labirint(is,js, 0, n , m, field, table);

     if (table[ie][je] == INT_MAX) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << table[ie][je] << std::endl;
    }

    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            std::cout<< field[i][j]<< ' ';
        std::cout<< std::endl;
    }





}
