#ifndef LAB2_STACKARRAY_HPP
#define LAB2_STACKARRAY_HPP

#include "exceptions.hpp"
#include "stack.hpp"

template<class T>
class StackArray : public Stack<T>
{
public:
  StackArray(int size_ = 10);

  ~StackArray() override;

  void push(const T &e) override;

  T pop() override;

  T getTop();

  bool isEmpty() override;

private:
  T *array;
  int top;
  int size;

  void swap(StackArray<T> &src);
};

template<class T>
StackArray<T>::StackArray(int size_)
{
  if (size_ <= 0)
  {
    throw WrongStackSize();
  }
  array = new T[size_ + 1];
  top = 0;
  size = size_;
}

template<class T>
StackArray<T>::~StackArray()
{
  delete[] array;
}

template<class T>
void StackArray<T>::push(const T &e)
{
  if (top == size + 1)
  {
    throw StackOverflow();
  }
  top++;
  array[top] = e;
}

template<class T>
T StackArray<T>::pop()
{
  if (top == 0)
  {
    throw StackUnderflow();
  }
  T temp = array[top];
  top--;
  return temp;
}

template<class T>
bool StackArray<T>::isEmpty()
{
  if (top == 0) return true;
  else return false;
}

template<class T>
void StackArray<T>::swap(StackArray<T> &src)
{

}

template<class T>
T StackArray<T>::getTop()
{
  return array[top];
}

#endif
