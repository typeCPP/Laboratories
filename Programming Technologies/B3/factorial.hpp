#ifndef B3_FACTORIAL_HPP
#define B3_FACTORIAL_HPP

#include <iterator>

namespace usanov
{
  class FactorialContainer
  {
  public:
    class const_iterator : public std::iterator<std::bidirectional_iterator_tag, size_t, ptrdiff_t, size_t, size_t>
    {
    public:
      bool operator==(const const_iterator &iter) const;
      bool operator!=(const const_iterator &iter) const;
      const_iterator &operator++();
      const_iterator &operator--();
      const_iterator operator++(int);
      const_iterator operator--(int);
      value_type operator*() const;
    private:
      const_iterator(size_t index,  size_t calculatedValue);
      size_t index;
      size_t value;
      friend FactorialContainer;
    };
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    FactorialContainer(size_t maxIndex = 0);
    const_iterator begin() const;
    const_iterator end() const;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
  private:
    const_iterator minValue;
    const_iterator maxValue;
  };

  size_t calculateFactorial(size_t num);
}
#endif
