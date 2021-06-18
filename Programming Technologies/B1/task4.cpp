#include "tasks.hpp"
#include <stdexcept>
#include <iostream>
#include "strategies.hpp"
#include "sort.hpp"

void fillRandom(double *array, int size)
{
  if (array == nullptr)
  {
    throw std::invalid_argument("Nullptr array");
  }
  for (int i = 0; i < size; i++)
  {
    array[i] = static_cast<double>(rand()) / (RAND_MAX / 2) - 1;
  }
}

std::vector<double> task4(const std::function<bool(double, double)> &typeOfSort, int size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Wrong vector size");
  }
  std::vector<double> vector(size);
  fillRandom(vector.data(), size);
  print(vector);
  std::cout << '\n';

  sortContainer<BracketsPolicy>(vector, typeOfSort);
  print(vector);
  return vector;
}
