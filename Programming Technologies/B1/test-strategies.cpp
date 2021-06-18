#include <stdexcept>
#include <vector>
#include <list>
#include <boost/test/unit_test.hpp>
#include "strategies.hpp"

BOOST_AUTO_TEST_SUITE(testStrategies)

  const int SIZE = 5;

  struct fixture
  {
    fixture() :
      list({4, 8, 2, 7, -13}),
      vector({4, 8, 2, 7, -13})
    {}

    std::list<int> list;
    std::vector<int> vector;
  };

  BOOST_FIXTURE_TEST_CASE(bracketsPolicyTest, fixture)
  {
    BOOST_CHECK(BracketsPolicy<std::vector<int>>::begin(vector) == 0);
    BOOST_CHECK(BracketsPolicy<std::vector<int>>::end(vector) == SIZE);
    for (int i = 0; i < SIZE; i++)
    {
      BOOST_CHECK(vector[i] == BracketsPolicy<std::vector<int>>::get(vector, i));
    }
  }

  BOOST_FIXTURE_TEST_CASE(atPolicyTest, fixture)
  {
    BOOST_CHECK(0 == AtMethodPolicy<std::vector<int>>::begin(vector));
    BOOST_CHECK(SIZE == AtMethodPolicy<std::vector<int>>::end(vector));
    for (int i = 0; i < SIZE; i++)
    {
      BOOST_CHECK(vector[i] == AtMethodPolicy<std::vector<int>>::get(vector, i));
    }
  }

  BOOST_FIXTURE_TEST_CASE(iteratorPolicyTest, fixture)
  {
    BOOST_CHECK(list.begin() == IteratorPolicy<std::list<int>>::begin(list));
    BOOST_CHECK(list.end() == IteratorPolicy<std::list<int>>::end(list));
    for (std::list<int>::iterator i = list.begin(); i != list.end(); i++)
    {
      BOOST_CHECK(IteratorPolicy<std::list<int>>::get(list, i) == *i);
    }
  }


  BOOST_FIXTURE_TEST_CASE(wrongArgument, fixture)
  {
    BOOST_CHECK_THROW(BracketsPolicy<std::vector<int>>::get(vector, -1), std::out_of_range);
    BOOST_CHECK_THROW(AtMethodPolicy<std::vector<int>>::get(vector, -1), std::out_of_range);
  }


BOOST_AUTO_TEST_SUITE_END()
