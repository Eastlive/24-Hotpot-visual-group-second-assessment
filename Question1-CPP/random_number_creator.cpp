#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;

const int DataSize = 100;
const int MinNumber = 0;
const int MaxNumber = 3;

void printRandomNumbers()
{
    srand(time(0));
    for (int i = 0; i < DataSize; i++)
    {
        cout << rand() % MaxNumber << endl;
    }
}

void printRandomNumbers2()
{
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<float> dist(MinNumber, MaxNumber);
    for (int i = 0; i < DataSize; i++)
    {
        cout << dist(mt) << endl;
    }
}

int main(int argc, char *argv[])
{
    cout << DataSize << endl;
    printRandomNumbers2();
    return 0;
}