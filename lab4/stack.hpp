#ifndef LAB2_STACK_HPP
#define LAB2_STACK_HPP

template<class T>
class Stack
{
public:
  virtual ~Stack() = default;

  virtual void push(const T &e) = 0;

  virtual T pop() = 0;

  virtual bool isEmpty() = 0;
};

#endif
