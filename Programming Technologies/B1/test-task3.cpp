#include <stdexcept>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "tasks.hpp"

BOOST_AUTO_TEST_SUITE(testTaskThree)

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

  BOOST_FIXTURE_TEST_CASE(testLastNumberIsNotOneOrTwo, fixture)
  {
    const std::string input = "1 2 4 6 8 3 9 6 0";
    in.str(input);
    task3();
    const std::string output = out.str();
    const std::string correctOutput = "1 2 4 6 8 3 9 6 ";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, correctOutput);
  }

  BOOST_FIXTURE_TEST_CASE(testLastNumberIsOne, fixture)
  {
    const std::string input = "1 2 4 6 8 3 9 1 0";
    in.str(input);
    task3();
    const std::string output = out.str();
    const std::string correctOutput = "1 3 9 1 ";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, correctOutput);
  }

  BOOST_FIXTURE_TEST_CASE(tastLastNumberIsTwo, fixture)
  {
    const std::string input = "1 2 3 4 5 6 9 2 0";
    in.str(input);
    task3();
    const std::string output = out.str();
    const std::string correctOutput = "1 2 3 1 1 1 4 5 6 1 1 1 9 1 1 1 2 ";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, correctOutput);
  }


BOOST_AUTO_TEST_SUITE_END()
