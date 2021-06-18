#include "tasks.hpp"
#include <vector>
#include <list>
#include <stdexcept>
#include <iostream>
#include "sort.hpp"
#include "strategies.hpp"

void task1(const std::function<bool(int, int)>& typeOfSort)
{
  int temp;
  std::vector<int> vectorForOperatorSort;
  while (std::cin >> temp)
  {
    vectorForOperatorSort.push_back(temp);
  }
  if (!std::cin.eof())
  {
    throw std::runtime_error("Input failed");
  }
  if (vectorForOperatorSort.empty())
  {
    return;
  }
  std::vector<int> vectorForAtSort(vectorForOperatorSort);
  std::list<int> listForIteratorSort(vectorForOperatorSort.begin(), vectorForOperatorSort.end());
  sortContainer<BracketsPolicy>(vectorForOperatorSort, typeOfSort);
  sortContainer<AtMethodPolicy>(vectorForAtSort, typeOfSort);
  sortContainer<IteratorPolicy>(listForIteratorSort, typeOfSort);
  print(vectorForOperatorSort);
  std::cout << '\n';
  print(vectorForAtSort);
  std::cout << '\n';
  print(listForIteratorSort);
  std::cout << '\n';
}
