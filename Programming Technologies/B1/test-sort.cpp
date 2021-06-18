#include <algorithm>
#include <stdexcept>
#include <vector>
#include <list>
#include <boost/test/unit_test.hpp>
#include "strategies.hpp"
#include "sort.hpp"

BOOST_AUTO_TEST_SUITE(testSort)

  const auto lessComparator = getOrderComparator<int>("ascending");
  const auto greaterComparator = getOrderComparator<int>("descending");

  struct fixture
  {
    fixture() :
      vector({4, 8, 2, 7, -13}),
      list({4, 8, 2, 7, -13}),
      sortedAscendingVector(vector),
      sortedAscendingList(list)
    {
      std::sort(sortedAscendingVector.begin(), sortedAscendingVector.end());
      sortedDescendingVector = sortedAscendingVector;
      std::reverse(sortedDescendingVector.begin(), sortedDescendingVector.end());
      sortedAscendingList.sort();
      sortedDescendingList = sortedAscendingList;
      sortedDescendingList.reverse();

    }
    std::vector<int> vector;
    std::list<int> list;
    std::vector<int> sortedAscendingVector;
    std::list<int> sortedAscendingList;
    std::vector<int> sortedDescendingVector;
    std::list<int> sortedDescendingList;
  };

  BOOST_FIXTURE_TEST_CASE(sortBracketsType, fixture)
  {
    sortContainer<BracketsPolicy>(vector, lessComparator);
    BOOST_CHECK(vector == sortedAscendingVector);
    sortContainer<BracketsPolicy>(vector, greaterComparator);
    BOOST_CHECK(vector == sortedDescendingVector);
  }

  BOOST_FIXTURE_TEST_CASE(sortAtType, fixture)
  {
    sortContainer<AtMethodPolicy>(vector, lessComparator);
    BOOST_CHECK(vector == sortedAscendingVector);
    sortContainer<AtMethodPolicy>(vector, greaterComparator);
    BOOST_CHECK(vector == sortedDescendingVector);
  }

  BOOST_FIXTURE_TEST_CASE(sortIteratorType, fixture)
  {
    sortContainer<IteratorPolicy>(list, lessComparator);
    BOOST_CHECK(list == sortedAscendingList);
    sortContainer<IteratorPolicy>(list, greaterComparator);
    BOOST_CHECK(list == sortedDescendingList);
  }

  BOOST_AUTO_TEST_CASE(comparatorTest)
  {
    const auto testAscendingComparator = getOrderComparator<int>("ascending");
    BOOST_CHECK_EQUAL(testAscendingComparator(1, 2), true);
    BOOST_CHECK_EQUAL(testAscendingComparator(2, 1), false);
    const auto testDescendingComparator = getOrderComparator<int>("descending");
    BOOST_CHECK_EQUAL(testDescendingComparator(1, 2), false);
    BOOST_CHECK_EQUAL(testDescendingComparator(2, 1), true);

    BOOST_CHECK_THROW(getOrderComparator<int>("testValue"), std::invalid_argument);
    BOOST_CHECK_THROW(getOrderComparator<int>(nullptr), std::invalid_argument);
  }


BOOST_AUTO_TEST_SUITE_END()
