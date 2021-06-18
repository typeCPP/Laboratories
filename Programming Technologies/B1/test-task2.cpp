#include <stdexcept>
#include <iostream>
#include <fstream>
#include <boost/test/unit_test.hpp>
#include "tasks.hpp"

BOOST_AUTO_TEST_SUITE(testTaskTwo)

  struct fixture
  {
    fixture() :
      cinBuf(std::cin.rdbuf(in.rdbuf())),
      coutBuf(std::cout.rdbuf(out.rdbuf()))
    {}

    void redirectInputOutput()
    {
      std::cin.rdbuf(cinBuf);
      std::cout.rdbuf(coutBuf);
    }

    std::streambuf *cinBuf;
    std::streambuf *coutBuf;
    std::istringstream in;
    std::ostringstream out;
  };

  BOOST_FIXTURE_TEST_CASE(testReadingFromFile, fixture)
  {
    const char *filename = "testInput.txt";
    std::ofstream outStream;
    outStream.open(filename);
    outStream << "a b c 1 2" << std::endl;
    task2(filename);
    const std::string output = out.str();
    redirectInputOutput();
    const std::string correctOutput = "a b c 1 2\n";
    BOOST_CHECK_EQUAL(output, correctOutput);
  }

  BOOST_AUTO_TEST_CASE(wrongFileName)
  {
    BOOST_CHECK_THROW(task2("randomName"), std::runtime_error);
    BOOST_CHECK_THROW(task2(nullptr), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
