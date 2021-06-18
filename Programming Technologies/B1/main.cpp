#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include "tasks.hpp"
#include "sort.hpp"

int main(int argc, char *argv[])
{
  if (argc <= 1)
  {
    std::cerr << "Wrong number of arguments";
    return 1;
  }
  std::istringstream numStream(argv[1]);
  int taskNumber = 0;
  numStream >> taskNumber;
  if (!numStream.eof() || taskNumber < 1 || taskNumber > 4)
  {
    std::cerr << "Wrong task number";
    return 1;
  }
  switch (taskNumber)
  {
    case 1:
    {
      if (argc != 3)
      {
        std::cerr << "Wrong number of arguments";
        return 1;
      }
      try
      {
        task1(getOrderComparator<int>(argv[2]));
      }
      catch (const std::runtime_error &error)
      {
        std::cerr << error.what() << "\n";
        return 1;
      }
      catch (const std::invalid_argument &error)
      {
        std::cerr << error.what() << "\n";
        return 1;
      }
      break;
    }
    case 2:
    {
      if (argc != 3)
      {
        std::cerr << "Wrong number of arguments";
        return 1;
      }
      try
      {
        task2(argv[2]);
      }
      catch (const std::invalid_argument &error)
      {
        std::cerr << error.what() << "\n";
        return 1;
      }
      catch (const std::runtime_error &error)
      {
        std::cerr << error.what() << "\n";
        return 1;
      }
      catch (const std::bad_alloc &error)
      {
        std::cerr << error.what() << "\n";
        return 1;
      }
      break;
    }
    case 3:
    {
      if (argc != 2)
      {
        std::cerr << "Wrong number of arguments";
        return 1;
      }
      try
      {
        task3();
      }
      catch (const std::runtime_error &error)
      {
        std::cerr << error.what() << "\n";
        return 1;
      }
      break;
    }
    case 4:
    {
      if (argc != 4)
      {
        std::cerr << "Wrong number of arguments";
        return 1;
      }
      std::srand(time(nullptr));
      std::istringstream countStream(argv[3]);
      int count = 0;
      countStream >> count;
      if (!countStream.eof())
      {
        std::cerr << "Wrong size parameter\n";
        return 1;
      }
      try
      {
        task4(getOrderComparator<double>(argv[2]), count);
      }
      catch (const std::invalid_argument &error)
      {
        std::cerr << error.what() << "\n";
        return 1;
      }
      break;
    }
    default:
    {
      std::cerr << "Wrong task number";
      return 1;
    }
  }
}
