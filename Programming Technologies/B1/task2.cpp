#include "tasks.hpp"
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <cstring>

void task2(const char *fileName)
{
  if (fileName == nullptr)
  {
    throw std::invalid_argument("Empty file name");
  }
  std::ifstream file(fileName);
  if (!file)
  {
    throw std::runtime_error("File not open");
  }
  size_t size = 512, count = 0;

  std::unique_ptr<char[], decltype(&free)> data(static_cast<char *>(malloc(size)), free);
  if (!data)
  {
    throw std::bad_alloc();
  }

  while (file)
  {
    file.read(&data[count], size - count);
    count += file.gcount();
    if (size == count)
    {
      size *= 2;
      std::unique_ptr<char[], decltype(&free)> temp(static_cast<char *>(realloc(data.get(), size)), &free);
      if (!temp)
      {
        throw std::bad_alloc();
      }
      data.release();
      data = std::move(temp);
    }
  }
  std::vector<char> textVector(data.get(), data.get() + count);

  std::cout.write(&textVector[0], textVector.size());
}
