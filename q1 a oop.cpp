#include <iostream>
using namespace std;

void change_location(char *array, int b1, int b2)
{
    if (b1 >= b2)
        return;

    char temp = array[b1];
    array[b1] = array[b2];
    array[b2] = temp;

    change_location(array, b1 + 1, b2 - 1);
}

int main()
{
    char array[8] = {'C', 'O', 'M', 'P', 'U', 'T', 'E', 'R'};

    int b1 = 2; 
    int b2 = 6; 

    change_location(array, b1, b2);

    cout << "After change: ";
    for (int i = 0; i < 8; i++)
        cout << array[i] << ' ';
    cout << endl;

    return 0;
}


