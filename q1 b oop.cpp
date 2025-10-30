#include <iostream>
using namespace std;

void printline(int a[], int size)
{
    for (int i = 0; i < size; i++)
        cout << a[i] << " ";
    cout << endl;
}

void printpatternrec(int a[], int size)
{
    printline(a, size);

    bool allone = true;
    for (int i = 0; i < size; i++)
        if (a[i] != 1)
            allone = false;
    if (allone)
        return;

    int b[20];
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (a[i] > 1)
        {
            if (a[i] == 4)
            {
                b[j++] = 2;
                b[j++] = 2;
            }
            else if (a[i] == 3)
            {
                b[j++] = 1;
                b[j++] = 2;
            }
            else if (a[i] == 2)
{
                b[j++] = 1;
                b[j++] = 1;
            }
        }
        else
        {
            b[j++] = a[i];
        }
    }

    printpatternrec(b, j);
}

void printpattern(int &n)
{
    int a[20];
    a[0] = n;
    printpatternrec(a, 1);
}

int main()
{
    int n;
    cout << "Enter any number = ";
    cin >> n;
    printpattern(n);
    return 0;
}
