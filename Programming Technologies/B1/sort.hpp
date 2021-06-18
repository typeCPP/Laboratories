#ifndef B1_SORT_HPP
#define B1_SORT_HPP

#include <functional>
#include <stdexcept>
#include <cstring>

template<typename T>
std::function<bool(const T &, const T &)> getOrderComparator(const char *order)
{
  if (order == nullptr)
  {
    throw std::invalid_argument("Null sortContainer order parameter");
  }

  if (std::strcmp(order, "ascending") == 0)
  {
    return std::less<T>();
  }

  if (std::strcmp(order, "descending") == 0)
  {
    return std::greater<T>();
  }

  throw std::invalid_argument("Invalid sortContainer parameter");
}

template<template<class Container> class Policy, typename Container>
void sortContainer(Container &container,
                   std::function<bool(typename Container::value_type, typename Container::value_type)> comparator)
{
  const auto begin = Policy<Container>::begin(container);
  const auto end = Policy<Container>::end(container);
  for (auto i = begin; i != end; i++)
  {
    auto checkElementIndex = i;
    typename Container::value_type checkElement = Policy<Container>::get(container, checkElementIndex);
    for (auto j = i; j != end; j++)
    {
      typename Container::value_type currentElement = Policy<Container>::get(container, j);
      checkElement = Policy<Container>::get(container, checkElementIndex);
      if (comparator(currentElement, checkElement))
      {
        checkElementIndex = j;
      }
    }

    if (checkElementIndex != i)
    {
      std::swap(Policy<Container>::get(container, i), Policy<Container>::get(container, checkElementIndex));
    }
  }
}

#endif
