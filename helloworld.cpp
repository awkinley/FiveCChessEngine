#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h> 

using namespace std;

int main()
{
    const int SIZE = 10000;
    auto bigArray = new int[SIZE][SIZE];
    for (size_t i = 0; i < SIZE; i++) 
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            bigArray[i][j] = rand() % 10;
        }
    }

    int sum = 0;
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            sum += bigArray[i][j];
        }
    }

    return sum;
    
}