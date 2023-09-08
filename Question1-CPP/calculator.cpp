#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <thread>
#include <chrono>
#include <random>

int DataSize;
std::vector<float> numbers;
std::vector<std::function<float(const std::vector<float> &)>> operations;

float sum(const std::vector<float> &numbers)
{
    float sum = 0.0;
    for (float number : numbers)
    {
        sum += number;
    }
    return sum;
}

float average(const std::vector<float> &numbers)
{
    return sum(numbers) / numbers.size();
}

float variance(const std::vector<float> &numbers)
{
    float averageValue = average(numbers);
    float variance = 0.0;
    for (float number : numbers)
    {
        variance += (number - averageValue) * (number - averageValue);
    }
    return variance / numbers.size();
}

float product(const std::vector<float> &numbers)
{
    float product = 1.0;
    for (float number : numbers)
    {
        product *= number;
    }
    return product;
}

void getNumbers()
{
    std::cin >> DataSize;
    for (int i = 0; i < DataSize; i++)
    {
        float number;
        std::cin >> number;
        numbers.push_back(number);
    }
}

void pushOperations()
{
    operations.push_back(sum);
    operations.push_back(average);
    operations.push_back(variance);
    operations.push_back(product);
}

void checkDataSize()
{
    std::cout << DataSize << std::endl;
}

void printNumbers()
{
    for (float number : numbers)
    {
        std::cout << number << std::endl;
    }
}

void createTimerLoop(int period, std::vector<float> &numbers, std::vector<std::function<float(const std::vector<float> &)>> &operations)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0, operations.size());
    while (true)
    {
        int index = dist(mt);
        std::cout << operations[index](numbers) << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(period));
    }
}

int main(int argc, char *argv[])
{
    pushOperations();
    getNumbers();
    checkDataSize();
    printNumbers();
    createTimerLoop(500, numbers, operations);
    return 0;
}