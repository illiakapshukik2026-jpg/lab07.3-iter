// Lab_7_3_Iter.cpp
// Капшук Ілля Віталійович
// Лабораторна робота № 7.3.
// Опрацювання динамічних багатовимірних масивів ітераційним способом.
// Варіант 6

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

void Create(int** a, const int k, const int n, const int Low, const int High);
void Input(int** a, const int k, const int n);
void Print(int** a, const int k, const int n);
bool RowHasNegative(int** a, const int rowNo, const int n);
int SumRow(int** a, const int rowNo, const int n);
int Part1_SumRowsWithNegative(int** a, const int k, const int n);

bool IsMinInRow(int** a, const int rowNo, const int colNo, const int n);
bool IsMaxInCol(int** a, const int rowNo, const int colNo, const int k);
void Part2_SaddlePoints(int** a, const int k, const int n);

int main()
{
    srand((unsigned)time(NULL));
    int k, n;
    cout << "Enter k (rows): "; cin >> k;
    cout << "Enter n (cols): "; cin >> n;

    int** a = new int* [k];
    for (int i = 0; i < k; i++)
        a[i] = new int[n];

    // Можна використовувати Input(a, k, n) або Create(a, k, n, -10, 20)
    Input(a, k, n);

    cout << "\nInitial Matrix:" << endl;
    Print(a, k, n);

    int sumVal = Part1_SumRowsWithNegative(a, k, n);
    cout << "Sum of elements in rows containing at least one negative element = " << sumVal << endl;

    cout << endl;
    Part2_SaddlePoints(a, k, n);

    for (int i = 0; i < k; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void Create(int** a, const int k, const int n, const int Low, const int High)
{
    for (int i = 0; i < k; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = Low + rand() % (High - Low + 1);
}

void Input(int** a, const int k, const int n)
{
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
    }
}

void Print(int** a, const int k, const int n)
{
    cout << endl;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setw(6) << a[i][j];
        cout << endl;
    }
    cout << endl;
}

bool RowHasNegative(int** a, const int rowNo, const int n)
{
    for (int j = 0; j < n; j++)
    {
        if (a[rowNo][j] < 0)
            return true;
    }
    return false;
}

int SumRow(int** a, const int rowNo, const int n)
{
    int s = 0;
    for (int j = 0; j < n; j++)
        s += a[rowNo][j];
    return s;
}

int Part1_SumRowsWithNegative(int** a, const int k, const int n)
{
    int totalSum = 0;
    for (int i = 0; i < k; i++)
    {
        if (RowHasNegative(a, i, n))
            totalSum += SumRow(a, i, n);
    }
    return totalSum;
}

bool IsMinInRow(int** a, const int rowNo, const int colNo, const int n)
{
    for (int j = 0; j < n; j++)
    {
        if (a[rowNo][j] < a[rowNo][colNo])
            return false;
    }
    return true;
}

bool IsMaxInCol(int** a, const int rowNo, const int colNo, const int k)
{
    for (int i = 0; i < k; i++)
    {
        if (a[i][colNo] > a[rowNo][colNo])
            return false;
    }
    return true;
}

void Part2_SaddlePoints(int** a, const int k, const int n)
{
    cout << "Saddle points (Min in Row & Max in Col):" << endl;
    cout << setw(6) << "No" << setw(8) << "Row" << setw(8) << "Col" << setw(10) << "Value" << endl;
    int count = 0;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (IsMinInRow(a, i, j, n) && IsMaxInCol(a, i, j, k))
            {
                count++;
                cout << setw(6) << count << setw(8) << i << setw(8) << j << setw(10) << a[i][j] << endl;
            }
        }
    }
    if (count == 0)
        cout << "No saddle points found." << endl;
}