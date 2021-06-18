#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "data-struct.hpp"

BOOST_AUTO_TEST_SUITE(testDataStruct)

  struct fixture
  {
    std::istringstream input;
    DataStruct dataStruct;
  };

  BOOST_FIXTURE_TEST_CASE(testIncorrectNumbers, fixture)
  {
    input.str("-6, 2,  exampleString");
    input >> dataStruct;
    BOOST_CHECK(!input);
    input.clear();

    input.str("1, 6,  exampleString");
    input >> dataStruct;
    BOOST_CHECK(!input);
    input.clear();

    input.str("6, 6,  exampleString");
    input >> dataStruct;
    BOOST_CHECK(!input);
    input.clear();
  }

  BOOST_FIXTURE_TEST_CASE(testMissingCommas, fixture)
  {
    input.str("1 2, exampleString");
    input >> dataStruct;
    BOOST_CHECK(!input);
    input.clear();

    input.str("1 2 exampleString");
    input >> dataStruct;
    BOOST_CHECK(!input);
    input.clear();

    input.str("1, 2 exampleString");
    input >> dataStruct;
    BOOST_CHECK(!input);
    input.clear();
  }

  BOOST_FIXTURE_TEST_CASE(testEmptyData, fixture)
  {
    input.str("1,, exampleString");
    input >> dataStruct;
    BOOST_CHECK(!input);
    input.clear();

    input.str(",, exampleString");
    input >> dataStruct;
    BOOST_CHECK(!input);
    input.clear();

    input.str("1, 2,");
    input >> dataStruct;
    BOOST_CHECK(!input);
    input.clear();
  }

  BOOST_FIXTURE_TEST_CASE(testCorrectInput, fixture)
  {
    input.str("1,       2,  exampleString");
    input >> dataStruct;
    BOOST_CHECK_EQUAL(dataStruct.key1, 1);
    BOOST_CHECK_EQUAL(dataStruct.key2, 2);
    BOOST_CHECK_EQUAL(dataStruct.str, "exampleString");
    BOOST_CHECK(input);
  }

  BOOST_AUTO_TEST_CASE(testComparsion)
  {
    ComparingDataStructs comp;
    DataStruct ds1 = {1, 1, "string"};
    DataStruct ds2 = {1, 1, "string2"};
    BOOST_CHECK(comp(ds1, ds2));

    ds1 = {1, 2, "string1"};
    ds2 = {1, 1, "string2"};
    BOOST_CHECK(!comp(ds1, ds2));

    ds1 = {-1, 1, "string1"};
    ds2 = {2, 1, "string2"};
    BOOST_CHECK(comp(ds1, ds2));
  }

BOOST_AUTO_TEST_SUITE_END()
