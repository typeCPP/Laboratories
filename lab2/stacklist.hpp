#ifndef LAB2_STACKLIST_HPP
#define LAB2_STACKLIST_HPP

#include "exceptions.hpp"
#include "stack.hpp"

template<class T>
class StackList : public Stack<T>
{
public:
  StackList();

  ~StackList() override;

  void push(const T &e) override;

  T pop() override;

  T getTop();

  bool isEmpty() override;

private:
  struct Node
  {
    T value;
    Node *prev;

    Node(T newValue, Node *prev_) :
      value(newValue), prev(prev_)
    {}

  };

  Node *top;
  int size;

  void swap(StackList<T> &src);
};

template<class T>
StackList<T>::StackList()
{
  size = 0;
  top = nullptr;
}

template<class T>
StackList<T>::~StackList()
{
  while (!isEmpty())
  {
    pop();
  }
}

template<class T>
void StackList<T>::push(const T &e)
{
  Node *temp = new Node(e, top);
  top = temp;
  size++;
}

template<class T>
T StackList<T>::pop()
{
  if (size == 0)
  {
    throw StackUnderflow();
  }
  size--;
  Node *temp = top;
  T tempValue = temp->value;
  top = top->prev;
  delete temp;
  return tempValue;
}

template<class T>
bool StackList<T>::isEmpty()
{
  if (size == 0) return true;
  else return false;
}

template<class T>
T StackList<T>::getTop()
{
  return top->value;
}

#endif
