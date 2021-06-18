#ifndef B4_UTILITY_HPP
#define B4_UTILITY_HPP

#include <istream>

class StreamGuard
{
public:
  StreamGuard(std::istream &input);
  ~StreamGuard();
private:
  std::istream &stream;
  std::istream::fmtflags flags;
};

std::istream &skipWs(std::istream &input);

#endif
