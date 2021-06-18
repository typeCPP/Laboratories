#include "factorial.hpp"
#include <stdexcept>

usanov::FactorialContainer::FactorialContainer(size_t maxIndex) :
  minValue(1, 1),
  maxValue(maxIndex + 1, calculateFactorial(maxIndex + 1))
{}

usanov::FactorialContainer::const_iterator usanov::FactorialContainer::begin() const
{
  return minValue;
}

usanov::FactorialContainer::const_iterator usanov::FactorialContainer::end() const
{
  return maxValue;
}

usanov::FactorialContainer::const_reverse_iterator usanov::FactorialContainer::rbegin() const
{
  return const_reverse_iterator(end());
}

usanov::FactorialContainer::const_reverse_iterator usanov::FactorialContainer::rend() const
{
  return const_reverse_iterator(begin());
}

usanov::FactorialContainer::const_iterator::const_iterator(size_t index_, size_t calculatedValue) :
  index(index_),
  value(calculatedValue)
{}

bool usanov::FactorialContainer::const_iterator::operator==(const const_iterator &iter) const
{
  return index == iter.index;
}

bool usanov::FactorialContainer::const_iterator::operator!=(const const_iterator &iter) const
{
  return index != iter.index;
}

usanov::FactorialContainer::const_iterator &usanov::FactorialContainer::const_iterator::operator++()
{
  index++;
  value *= index;
  return *this;
}

usanov::FactorialContainer::const_iterator &usanov::FactorialContainer::const_iterator::operator--()
{
  if (index <= 0)
  {
    throw std::out_of_range("Out of container bounds");
  }
  value /= index;
  index--;
  return *this;
}

usanov::FactorialContainer::const_iterator usanov::FactorialContainer::const_iterator::operator++(int)
{
  const_iterator temp = *this;
  temp.index++;
  temp.value *= temp.index;
  return temp;
}

usanov::FactorialContainer::const_iterator usanov::FactorialContainer::const_iterator::operator--(int)
{
  if (index <= 0)
  {
    throw std::out_of_range("Out of container bounds");
  }
  const_iterator temp = *this;
  temp.value /= temp.index;
  temp.index--;
  return temp;
}

usanov::FactorialContainer::const_iterator::value_type usanov::FactorialContainer::const_iterator::operator*() const
{
  return value;
}

size_t usanov::calculateFactorial(size_t num)
{
  size_t result = 1;
  for (size_t i = 1; i <= num; i++)
  {
    if (result > SIZE_MAX / i)
    {
      throw std::overflow_error("Factorial overflow");
    }
    result *= i;
  }
  return result;
}

