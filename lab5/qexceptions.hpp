#ifndef LAB5_QEXCEPTIONS_HPP
#define LAB5_QEXCEPTIONS_HPP

#include <stdexcept>
#include <iostream>

class QueueOverflow : public std::exception
{
public:
  QueueOverflow() : reason_("Queue Overflow")
  {}

  const char *what() const noexcept override
  {
    return reason_.c_str();
  }

private:
  const std::string reason_;
};

class QueueUnderflow : public std::exception
{
public:
  QueueUnderflow() : reason_("Queue Underflow")
  {}

  const char *what() const noexcept override
  {
    return reason_.c_str();
  }

private:
  const std::string reason_;
};

class WrongQueueSize : public std::exception
{
public:
  WrongQueueSize() : reason_("Wrong queue size")
  {}

  const char *what() const noexcept override
  {
    return reason_.c_str();
  }

private:
  const std::string reason_;
};

#endif
