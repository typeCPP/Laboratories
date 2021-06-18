#include "tasks.hpp"
#include <vector>
#include <stdexcept>
#include <iostream>

void task3()
{
  std::vector<int> vector;
  int number = 0;
  while (std::cin >> number)
  {
    if (number == 0)
    {
      break;
    }
    vector.push_back(number);
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Incorrect input");
  }
  if (vector.empty())
  {
    return;
  }
  if (number != 0)
  {
    throw std::runtime_error("Input end symbol not found");
  }

  if (vector.back() == 1)
  {
    for (std::vector<int>::iterator i = vector.begin(); i != vector.end();)
    {
      if (*i % 2 == 0)
      {
        i = vector.erase(i);
      }
      else
      {
        i++;
      }
    }
  }
  else if (vector.back() == 2)
  {
    for (std::vector<int>::iterator i = vector.begin(); i != vector.end();)
    {
      if (*i % 3 == 0)
      {
        i = vector.insert(i + 1, 3, 1) + 3;
      }
      else
      {
        i++;
      }
    }
  }

  print(vector);
}
