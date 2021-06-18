#include <stdexcept>
#include <vector>
#include <boost/test/unit_test.hpp>
#include "tasks.hpp"
#include "sort.hpp"

BOOST_AUTO_TEST_SUITE(testTaskFour)
  const int SIZE = 5;

  BOOST_AUTO_TEST_CASE(testFillRandomFunction)
  {
    std::vector<double> vector(SIZE, 0);
    fillRandom(vector.data(), SIZE);
    for (int i = 0; i < SIZE; i++)
    {
      BOOST_CHECK(vector[i] <= 1 && vector[i] >= -1);
    }
  }

  BOOST_AUTO_TEST_CASE(testVectorAscendingSort)
  {
    std::vector<double> testVector;
    testVector = task4(getOrderComparator<double>("ascending"), SIZE);
    for (int i = 1; i < SIZE; i++)
    {
      BOOST_CHECK(testVector[i] <= 1 && testVector[i] >= -1);
      BOOST_CHECK(testVector[i] >= testVector[i - 1]);
    }
  }

  BOOST_AUTO_TEST_CASE(testVectorDescendingSort)
  {
    std::vector<double> testVector;
    testVector = task4(getOrderComparator<double>("descending"), SIZE);
    for (int i = 1; i < SIZE; i++)
    {
      BOOST_CHECK(testVector[i] <= 1 && testVector[i] >= -1);
      BOOST_CHECK(testVector[i] <= testVector[i - 1]);
    }
  }

  BOOST_AUTO_TEST_CASE(testWrongArgument)
  {
    BOOST_CHECK_THROW(fillRandom(nullptr, 10), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
