#ifndef LAB2_EXCEPTIONS_HPP
#define LAB2_EXCEPTIONS_HPP

#include <exception>
#include <iostream>

class StackOverflow : public std::exception
{
public:
  StackOverflow() : reason_("Stack Overflow")
  {}

  const char *what() const noexcept override
  {
    return reason_.c_str();
  }

private:
  const std::string reason_;
};

class StackUnderflow : public std::exception
{
public:
  StackUnderflow() : reason_("Stack Underflow")
  {}

  const char *what() const noexcept override
  {
    return reason_.c_str();
  }

private:
  const std::string reason_;
};

class WrongStackSize : public std::exception
{
public:
  WrongStackSize() : reason_("Wrong stack size")
  {}

  const char *what() const noexcept override
  {
    return reason_.c_str();
  }

private:
  const std::string reason_;
};

class GraphEmpty : public std::exception
{
public:
  GraphEmpty() : reason_("The graph is empty")
  {}

  const char *what() const noexcept override
  {
    return reason_.c_str();
  }

private:
  const std::string reason_;
};

#endif
