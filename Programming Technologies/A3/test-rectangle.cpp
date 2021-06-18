#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(testRectangle)

  const double EPSILON = 0.0001;
  const double TEST_HEIGHT = 20.0;
  const double TEST_WIDTH = 4.5;
  const double TEST_FACT = 2.0;
  const usanov::point_t TEST_POS = {1.0, 5.0};

  BOOST_AUTO_TEST_CASE(rectangleCorrectData)
  {
    usanov::Rectangle testRect(TEST_WIDTH, TEST_HEIGHT, TEST_POS);
    BOOST_CHECK_CLOSE(testRect.getWidth(), TEST_WIDTH, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getHeight(), TEST_HEIGHT, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getArea(), TEST_HEIGHT * TEST_WIDTH, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.x, TEST_POS.x, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.y, TEST_POS.y, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().height, TEST_HEIGHT, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().width, TEST_WIDTH, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectMoveOnPoint)
  {
    usanov::Rectangle testRect({TEST_WIDTH, TEST_HEIGHT, TEST_POS});
    const double CHECK_AREA = testRect.getArea();
    const usanov::point_t TEST_NEW_POINT = {50.5, 102.6};
    testRect.move(TEST_NEW_POINT);
    BOOST_CHECK_CLOSE(testRect.getWidth(), TEST_WIDTH, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getHeight(), TEST_HEIGHT, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getArea(), CHECK_AREA, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.x, TEST_NEW_POINT.x, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.y, TEST_NEW_POINT.y, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().height, TEST_HEIGHT, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().width, TEST_WIDTH, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectMoveOnCoordinates)
  {
    usanov::Rectangle testRect({TEST_WIDTH, TEST_HEIGHT, TEST_POS});
    const double DX = 102.4, DY = 11.5, CHECK_AREA = testRect.getArea();
    testRect.move(DX, DY);
    BOOST_CHECK_CLOSE(testRect.getWidth(), TEST_WIDTH, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getHeight(), TEST_HEIGHT, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getArea(), CHECK_AREA, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.x, TEST_POS.x + DX, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.y, TEST_POS.y + DY, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().height, TEST_HEIGHT, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().width, TEST_WIDTH, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectScalingSquare)
  {
    usanov::Rectangle testRect({TEST_WIDTH, TEST_HEIGHT, TEST_POS});
    const double CHECK_AREA = testRect.getArea();
    testRect.scale(TEST_FACT);
    BOOST_CHECK_CLOSE(testRect.getWidth(), TEST_WIDTH * TEST_FACT, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getHeight(), TEST_HEIGHT * TEST_FACT, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getArea(), CHECK_AREA * TEST_FACT * TEST_FACT, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.x, TEST_POS.x, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.y, TEST_POS.y, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().height, TEST_HEIGHT * TEST_FACT, EPSILON);
    BOOST_CHECK_CLOSE(testRect.getFrameRect().width, TEST_WIDTH * TEST_FACT, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectWrongScaling)
  {
    usanov::Rectangle testRect({TEST_WIDTH, TEST_HEIGHT, TEST_POS});
    BOOST_CHECK_THROW(testRect.scale(-5.0), std::invalid_argument);
    BOOST_CHECK_THROW(testRect.scale(0.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rectInvalidParameters)
  {
    BOOST_CHECK_THROW(usanov::Rectangle testRect(10.0, 0.0, TEST_POS), std::invalid_argument);
    BOOST_CHECK_THROW(usanov::Rectangle testRect(-10.0, 0.0, TEST_POS), std::invalid_argument);
    BOOST_CHECK_THROW(usanov::Rectangle testRect(-10.0, -5.0, TEST_POS), std::invalid_argument);
    BOOST_CHECK_THROW(usanov::Rectangle testRect(-10.0, 10.0, TEST_POS), std::invalid_argument);
    BOOST_CHECK_THROW(usanov::Rectangle testRect(0.0, 0.0, TEST_POS), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
