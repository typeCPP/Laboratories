#include <vector>
#include <stdexcept>
#include <iterator>
#include <iostream>
#include <algorithm>
#include "data-struct.hpp"

void task(std::istream &input, std::ostream &output);

int main()
{
  try
  {
    task(std::cin, std::cout);
  }
  catch (const std::runtime_error &error)
  {
    std::cerr << error.what();
    return 2;
  }
  return 0;
}

void task(std::istream &input, std::ostream &output)
{
  std::vector<DataStruct> vector((std::istream_iterator<DataStruct>(input)), std::istream_iterator<DataStruct>());
  if (!std::cin.eof())
  {
    throw std::runtime_error("Incorrect input\n");
  }
  std::sort(vector.begin(), vector.end(), ComparingDataStructs());
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(output, "\n"));
}
