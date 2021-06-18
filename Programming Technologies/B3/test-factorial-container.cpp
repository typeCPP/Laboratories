#include <sstream>
#include <iostream>
#include <string>
#include <boost/test/unit_test.hpp>
#include "factorial.hpp"

BOOST_AUTO_TEST_SUITE(testFactorialContainer)

  struct fixture
  {
    fixture() :
      coutBuf(std::cout.rdbuf(out.rdbuf()))
    {}

    void redirectInputOutput()
    {
      std::cout.rdbuf(coutBuf);
    }

    std::streambuf *coutBuf;
    std::ostringstream out;
  };

  BOOST_AUTO_TEST_CASE(testEmptyContaier)
  {
    usanov::FactorialContainer factorial;
    auto iter = factorial.begin();
    BOOST_CHECK_EQUAL(*iter, 1);
    iter = factorial.end();
    BOOST_CHECK_EQUAL(*iter, 1);
  }

  BOOST_AUTO_TEST_CASE(testBeginAndEnd)
  {
    usanov::FactorialContainer factorial(10);
    BOOST_CHECK_EQUAL(*factorial.begin(), 1);
    BOOST_CHECK_EQUAL(*factorial.end(), 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11);
    BOOST_CHECK_EQUAL(*factorial.rbegin(), 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10);
    BOOST_CHECK_EQUAL(*factorial.rend(), 1);
  }

  BOOST_AUTO_TEST_CASE(testContainerOverflow)
  {
    BOOST_CHECK_THROW(usanov::FactorialContainer factorial(200), std::overflow_error);
  }

BOOST_AUTO_TEST_SUITE_END()
