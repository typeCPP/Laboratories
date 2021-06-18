#include <cmath>
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "circle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(testCircle)

  const double EPSILON = 0.0001;
  const double TEST_RAD = 13.0;
  const double TEST_FACT = 2.0;
  const usanov::point_t TEST_POS = {1.0, 5.0};

  BOOST_AUTO_TEST_CASE(circleCorrectData)
  {
    usanov::Circle testCircle(TEST_RAD, TEST_POS);
    BOOST_CHECK_CLOSE(testCircle.getRadius(), TEST_RAD, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getArea(), M_PI * TEST_RAD * TEST_RAD, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.x, TEST_POS.x, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.y, TEST_POS.y, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().height, 2 * TEST_RAD, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().width, 2 * TEST_RAD, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circleMoveOnPoint)
  {
    usanov::Circle testCircle(TEST_RAD, TEST_POS);
    const usanov::point_t TEST_NEW_POINT = {50.5, 102.6};
    const double CHECK_AREA = testCircle.getArea();
    testCircle.move(TEST_NEW_POINT);
    BOOST_CHECK_CLOSE(testCircle.getRadius(), TEST_RAD, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getArea(), CHECK_AREA, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.x, TEST_NEW_POINT.x, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.y, TEST_NEW_POINT.y, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().height, 2 * TEST_RAD, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().width, 2 * TEST_RAD, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circleMoveOnCoorditanes)
  {
    usanov::Circle testCircle(TEST_RAD, TEST_POS);
    const double DX = 102.4, DY = 11.5, CHECK_AREA = testCircle.getArea();
    testCircle.move(DX, DY);
    BOOST_CHECK_CLOSE(testCircle.getRadius(), TEST_RAD, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getArea(), CHECK_AREA, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.x, TEST_POS.x + DX, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.y, TEST_POS.y + DY, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().height, 2 * TEST_RAD, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().width, 2 * TEST_RAD, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circleScaling)
  {
    usanov::Circle testCircle(TEST_RAD, TEST_POS);
    const double CHECK_AREA = testCircle.getArea();
    testCircle.scale(TEST_FACT);
    BOOST_CHECK_CLOSE(testCircle.getRadius(), TEST_RAD * TEST_FACT, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getArea(), CHECK_AREA * TEST_FACT * TEST_FACT, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.x, TEST_POS.x, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.y, TEST_POS.y, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().height, TEST_FACT * TEST_RAD * 2, EPSILON);
    BOOST_CHECK_CLOSE(testCircle.getFrameRect().width, TEST_FACT * TEST_RAD * 2, EPSILON);

  }

  BOOST_AUTO_TEST_CASE(circleInvalidScaling)
  {
    usanov::Circle testCircle(TEST_RAD, TEST_POS);
    BOOST_CHECK_THROW(testCircle.scale(-5.0), std::invalid_argument);
    BOOST_CHECK_THROW(testCircle.scale(0.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(circleInvalidRadius)
  {
    BOOST_CHECK_THROW(usanov::Circle testCircle(0.0, TEST_POS), std::invalid_argument);
    BOOST_CHECK_THROW(usanov::Circle testCircle(-200, TEST_POS), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
