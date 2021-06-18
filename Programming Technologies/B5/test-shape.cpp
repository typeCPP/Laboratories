#include <boost/test/unit_test.hpp>
#include "shape.hpp"

BOOST_AUTO_TEST_SUITE(testShape)

  BOOST_AUTO_TEST_CASE(testPointOperators)
  {
    Point testPoint{};
    std::istringstream input("    (  1  ;  0 )");
    input >> testPoint;
    BOOST_CHECK_EQUAL(testPoint.x, 1);
    BOOST_CHECK_EQUAL(testPoint.y, 0);

    std::ostringstream output;
    const std::string rightOutput = "(1;0)";
    output << testPoint;
    BOOST_CHECK_EQUAL(output.str(), rightOutput);
  }

  BOOST_AUTO_TEST_CASE(testPointWrongInput)
  {
    Point testPoint{};
    std::istringstream input;

    input.str("[1;0]");
    input >> testPoint;
    BOOST_CHECK(!input);
    input.clear();

    input.str("[1 0]");
    input >> testPoint;
    BOOST_CHECK(!input);
    input.clear();

    input.str("(1;0]");
    input >> testPoint;
    BOOST_CHECK(!input);
    input.clear();

    input.str("(1 0)");
    input >> testPoint;
    BOOST_CHECK(!input);
    input.clear();
  }

  BOOST_AUTO_TEST_CASE(testShapeOperators)
  {
    Shape testShape;
    std::istringstream input("  4   (0;0 ) (0; 1)   (1   ;1) (1  ;0    )");
    input >> testShape;
    BOOST_CHECK_EQUAL(testShape.size(), 4);
    const std::string rightOutput = "4 (0;0) (0;1) (1;1) (1;0) ";
    std::ostringstream output;
    output << testShape;
    BOOST_CHECK_EQUAL(output.str(), rightOutput);
  }

  BOOST_AUTO_TEST_CASE(testShapeWrongInput)
  {
    Shape testShape;
    std::istringstream input;
    input.str("3 (0;0) (0;1)");
    input >> testShape;
    BOOST_CHECK(!input);
    input.clear();

    input.str("4 (0;0) (0;1) (1;1) {1;0}");
    input >> testShape;
    BOOST_CHECK(!input);
    input.clear();

    input.str("4 (0;0) (0;1) (1;1) (1;0");
    input >> testShape;
    BOOST_CHECK(!input);
    input.clear();

    input.str("4 (0;0) (0;1) (1;1) (1;0) (3;0)");
    input >> testShape;
    BOOST_CHECK(!input);
    input.clear();

    input.str("4 (0;0) (0;1)");
    input >> testShape;
    BOOST_CHECK(!input);
    input.clear();
  }

  BOOST_AUTO_TEST_CASE(testDetectionOfFigureType)
  {
    Shape testTriangle{{0, 0}, {0, 1}, {1, 0}};
    BOOST_CHECK(isTriangle(testTriangle));
    BOOST_CHECK(!isRectangle(testTriangle));
    BOOST_CHECK(!isSquare(testTriangle));
    BOOST_CHECK(!isPentagon(testTriangle));

    Shape testSquare{{0, 0}, {0, 1}, {1, 1}, {1, 0}};
    BOOST_CHECK(!isTriangle(testSquare));
    BOOST_CHECK(isRectangle(testSquare));
    BOOST_CHECK(isSquare(testSquare));
    BOOST_CHECK(!isPentagon(testSquare));

    Shape testRectangle{{0, 0}, {0, 2}, {1, 2}, {1, 0}};
    BOOST_CHECK(!isTriangle(testRectangle));
    BOOST_CHECK(isRectangle(testRectangle));
    BOOST_CHECK(!isSquare(testRectangle));
    BOOST_CHECK(!isPentagon(testRectangle));

    Shape testPentagon{{0, 0}, {-1, 1}, {1, 2}, {3, 1}, {2, 0}};
    BOOST_CHECK(!isTriangle(testPentagon));
    BOOST_CHECK(!isRectangle(testPentagon));
    BOOST_CHECK(!isSquare(testPentagon));
    BOOST_CHECK(isPentagon(testPentagon));
  }

  BOOST_AUTO_TEST_CASE(testGetSquaredDistance)
  {
    BOOST_CHECK_EQUAL(getSquaredDistance({0, 0}, {0, 2}), 4);
    BOOST_CHECK_EQUAL(getSquaredDistance({0, 0}, {2, 0}), 4);
    BOOST_CHECK_EQUAL(getSquaredDistance({0, 0}, {0, 0}), 0);
    BOOST_CHECK_EQUAL(getSquaredDistance({-100, 0}, {0, 0}), 10000);
  }

  BOOST_AUTO_TEST_CASE(testShapesComparator)
  {
    Shape testTriangle{{0, 0}, {0, 1}, {1, 0}};
    Shape testSquare{{0, 0}, {0, 1}, {1, 1}, {1, 0}};
    Shape testRectangle{{0, 0}, {0, 2}, {1, 2}, {1, 0}};
    BOOST_CHECK(ShapesComparator()(testTriangle, testRectangle));
    BOOST_CHECK(ShapesComparator()(testTriangle, testSquare));
    BOOST_CHECK(ShapesComparator()(testSquare, testRectangle));
    BOOST_CHECK(!ShapesComparator()(testRectangle, testSquare));
  }


BOOST_AUTO_TEST_SUITE_END()
