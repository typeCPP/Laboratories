#include <iostream>
#include <sstream>
#include <stdexcept>
#include "parser.hpp"
#include "factorial.hpp"

void task1();
void task2();

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Wrong number of arguments\n";
    return 1;
  }
  std::istringstream num(argv[1]);
  int taskNumber = 0;
  num >> taskNumber;
  if ((taskNumber > 2) || (taskNumber < 1) || (!num.eof()))
  {
    std::cerr << "Wrong task number\n";
    return 1;
  }
  if (taskNumber == 1)
  {
    task1();
  }
  else if (taskNumber == 2)
  {
    try
    {
      task2();
    }
    catch (const std::out_of_range &error)
    {
      std::cerr << error.what() << "\n";
      return 2;
    }
    catch (const std::overflow_error &error)
    {
      std::cerr << error.what() << "\n";
      return 2;
    }
  }
  return 0;
}

void task1()
{
  std::string command;
  usanov::BookmarkInterface phonebook;
  while (std::getline(std::cin, command))
  {
    Command commandToExecute = parseTypeOfCommand(command);
    commandToExecute(phonebook, std::cout);
  }
}

void task2()
{
  usanov::FactorialContainer factorial(10);
  std::copy(factorial.begin(), factorial.end(), std::ostream_iterator<unsigned int>(std::cout, " "));
  std::cout << '\n';
  std::copy(factorial.rbegin(), factorial.rend(), std::ostream_iterator<unsigned int>(std::cout, " "));
  std::cout << '\n';
}
