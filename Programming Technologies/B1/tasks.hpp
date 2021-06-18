#ifndef B1_TASKS_HPP
#define B1_TASKS_HPP

#include <iostream>
#include <functional>
#include <vector>

template<typename Container>
void print(const Container &container)
{
  for (const auto &element : container)
  {
    std::cout << element << ' ';
  }
}

void fillRandom(double *array, int size);
void task1(const std::function<bool(int, int)> &typeOfSort);
void task2(const char *fileName);
void task3();
std::vector<double> task4(const std::function<bool(double, double)> &typeOfSort, int size);

#endif
