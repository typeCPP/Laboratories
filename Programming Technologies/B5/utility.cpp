#include "utility.hpp"
#include <istream>

std::istream &skipWs(std::istream &input)
{
  while (std::isblank(input.peek()))
  {
    input.get();
  }
  return input;
}

StreamGuard::StreamGuard(std::istream &input) :
  stream(input),
  flags(input.flags())
{}

StreamGuard::~StreamGuard()
{
  stream.setf(flags);
}
