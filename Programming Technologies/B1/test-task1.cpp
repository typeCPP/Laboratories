#include <stdexcept>
#include <vector>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "tasks.hpp"
#include "sort.hpp"

BOOST_AUTO_TEST_SUITE(testTaskOne)

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

  BOOST_FIXTURE_TEST_CASE(testAscendingOrder, fixture)
  {
    const std::string input = "5 2 6 7 -4 12\n";
    in.str(input);
    task1(getOrderComparator<int>("ascending"));
    const std::string output = out.str();
    const std::string rightOutput = "-4 2 5 6 7 12 \n-4 2 5 6 7 12 \n-4 2 5 6 7 12 \n";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
  }

  BOOST_FIXTURE_TEST_CASE(testDescendingOrder, fixture)
  {
    const std::string input = "5 2 6 7 -4 12\n";
    in.str(input);
    task1(getOrderComparator<int>("descending"));
    const std::string output = out.str();
    const std::string rightOutput = "12 7 6 5 2 -4 \n12 7 6 5 2 -4 \n12 7 6 5 2 -4 \n";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
  }

BOOST_AUTO_TEST_SUITE_END()
