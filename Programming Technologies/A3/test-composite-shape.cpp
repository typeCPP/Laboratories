#include <stdexcept>
#include <memory>
#include <boost/test/unit_test.hpp>
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(testCompShape)

  const double EPSILON = 0.0001;
  const double TEST_RAD = 5.0;
  const double TEST_WIDTH = 10.0;
  const double TEST_HEIGHT = 10.0;
  const double TEST_FACT = 2.0;
  const usanov::point_t TEST_POS_CIRCLE = {15.0, 5.0};
  const usanov::point_t TEST_POS_CIRCLE2 = {30.0, 5.0};
  const usanov::point_t TEST_POS_RECTANGLE = {15.0, 15.0};
  const usanov::point_t TEST_POS_NEW_POINT = {1.0, 3.0};

  struct fixture
  {
    usanov::CompositeShape compShape;

    fixture()
    {
      usanov::Circle testCircle(TEST_RAD, TEST_POS_CIRCLE);
      usanov::Rectangle testRectangle(TEST_WIDTH, TEST_HEIGHT, TEST_POS_RECTANGLE);
      compShape.append(std::make_shared<usanov::Circle>(testCircle));
      compShape.append(std::make_shared<usanov::Rectangle>(testRectangle));
    }
  };

  BOOST_FIXTURE_TEST_CASE(compShapeBasicTest, fixture)
  {
    const double sumOfAreas = compShape[0]->getArea() + compShape[1]->getArea();
    const double compositeShapeCentreX = (compShape[0]->getFrameRect().pos.x + compShape[1]->getFrameRect().pos.x) / 2;
    const double compositeShapeCentreY = (compShape[0]->getFrameRect().pos.y + compShape[1]->getFrameRect().pos.y) / 2;
    const double compositeShapeWidth = (TEST_RAD * 2 + TEST_WIDTH) / 2;
    const double compositeShapeHeight = TEST_RAD * 2 + TEST_HEIGHT;
    BOOST_CHECK_EQUAL(compShape.getSize(), 2);
    BOOST_CHECK_CLOSE(compShape.getArea(), sumOfAreas, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.x, compositeShapeCentreX, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.y, compositeShapeCentreY, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().width, compositeShapeWidth, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().height, compositeShapeHeight, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(compShapeEmptyConstructor)
  {
    usanov::CompositeShape emptyCompShape;
    BOOST_CHECK_EQUAL(emptyCompShape.getSize(), 0);
    BOOST_CHECK_THROW(emptyCompShape.getArea(), std::logic_error);
    BOOST_CHECK_THROW(emptyCompShape.remove(0), std::out_of_range);
    BOOST_CHECK_THROW(emptyCompShape.getFrameRect(), std::logic_error);
    BOOST_CHECK_THROW(emptyCompShape.move(-4.5, 5.0), std::logic_error);
    BOOST_CHECK_THROW(emptyCompShape.scale(5.0), std::logic_error);

  }

  BOOST_FIXTURE_TEST_CASE(compShapeCopyConstructor, fixture)
  {
    usanov::CompositeShape copiedCompShape(compShape);

    BOOST_CHECK_EQUAL(copiedCompShape.getSize(), compShape.getSize());
    BOOST_CHECK_CLOSE(copiedCompShape.getFrameRect().height, compShape.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(copiedCompShape.getFrameRect().width, compShape.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(copiedCompShape.getFrameRect().pos.x, compShape.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(copiedCompShape.getFrameRect().pos.y, compShape.getFrameRect().pos.y, EPSILON);
  }

  BOOST_FIXTURE_TEST_CASE(compShapeMoveConstructor, fixture)
  {
    const double originalArea = compShape.getArea();
    const double originalFrameHeight = compShape.getFrameRect().height;
    const double originalFrameWidth = compShape.getFrameRect().width;
    const double originalFramePosX = compShape.getFrameRect().pos.x;
    const double originalFramePosY = compShape.getFrameRect().pos.y;
    const size_t originalSize = compShape.getSize();
    usanov::CompositeShape testCompositeShape(std::move(compShape));

    BOOST_CHECK_CLOSE(testCompositeShape.getArea(), originalArea, EPSILON);
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().height, originalFrameHeight, EPSILON);
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().width, originalFrameWidth, EPSILON);
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().pos.x, originalFramePosX, EPSILON);
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().pos.y, originalFramePosY, EPSILON);
    BOOST_CHECK_EQUAL(testCompositeShape.getSize(), originalSize);

    BOOST_CHECK_EQUAL(compShape.getSize(), 0);
    BOOST_CHECK_THROW(compShape.getArea(), std::logic_error);
    BOOST_CHECK_THROW(compShape.remove(0), std::out_of_range);
    BOOST_CHECK_THROW(compShape.getFrameRect(), std::logic_error);
    BOOST_CHECK_THROW(compShape.move(-4.5, 5.0), std::logic_error);
    BOOST_CHECK_THROW(compShape.scale(5.0), std::logic_error);
  }

  BOOST_FIXTURE_TEST_CASE(compShapeMoveOnPoint, fixture)
  {
    const double originalArea = compShape.getArea();
    const double originalFrameHeight = compShape.getFrameRect().height;
    const double originalFrameWidth = compShape.getFrameRect().width;

    compShape.move(TEST_POS_NEW_POINT);

    BOOST_CHECK_CLOSE(compShape.getArea(), originalArea, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().height, originalFrameHeight, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().width, originalFrameWidth, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.x, TEST_POS_NEW_POINT.x, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.y, TEST_POS_NEW_POINT.y, EPSILON);
  }

  BOOST_FIXTURE_TEST_CASE(compShapeMoveOnCoordinates, fixture)
  {
    const double originalArea = compShape.getArea();
    const double originalFrameHeight = compShape.getFrameRect().height;
    const double originalFrameWidth = compShape.getFrameRect().width;
    const double originalFramePosX = compShape.getFrameRect().pos.x;
    const double originalFramePosY = compShape.getFrameRect().pos.y;

    compShape.move(TEST_POS_NEW_POINT.x, TEST_POS_NEW_POINT.y);

    BOOST_CHECK_CLOSE(compShape.getArea(), originalArea, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().height, originalFrameHeight, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().width, originalFrameWidth, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.x, originalFramePosX + TEST_POS_NEW_POINT.x, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.y, originalFramePosY + TEST_POS_NEW_POINT.y, EPSILON);
  }

  BOOST_FIXTURE_TEST_CASE(compShapeScaling, fixture)
  {
    const double originalArea = compShape.getArea();
    const double originalFrameHeight = compShape.getFrameRect().height;
    const double originalFrameWidth = compShape.getFrameRect().width;
    const double originalFramePosX = compShape.getFrameRect().pos.x;
    const double originalFramePosY = compShape.getFrameRect().pos.y;
    const usanov::point_t centre = compShape.getFrameRect().pos;
    const double newCirclePosX = centre.x + TEST_FACT * (compShape[0]->getFrameRect().pos.x - centre.x);
    const double newCirclePosY = centre.y + TEST_FACT * (compShape[0]->getFrameRect().pos.y - centre.y);
    const double newRectanglePosX = centre.x + TEST_FACT * (compShape[1]->getFrameRect().pos.x - centre.x);
    const double newRectanglePosY = centre.y + TEST_FACT * (compShape[1]->getFrameRect().pos.y - centre.y);

    compShape.scale(TEST_FACT);

    BOOST_CHECK_CLOSE(compShape.getArea(), originalArea * TEST_FACT * TEST_FACT, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().height, originalFrameHeight * TEST_FACT, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().width, originalFrameWidth * TEST_FACT, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.x, originalFramePosX, EPSILON);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.y, originalFramePosY, EPSILON);

    BOOST_CHECK_CLOSE(compShape[0]->getFrameRect().pos.x, newCirclePosX, EPSILON);
    BOOST_CHECK_CLOSE(compShape[0]->getFrameRect().pos.y, newCirclePosY, EPSILON);
    BOOST_CHECK_CLOSE(compShape[1]->getFrameRect().pos.x, newRectanglePosX, EPSILON);
    BOOST_CHECK_CLOSE(compShape[1]->getFrameRect().pos.y, newRectanglePosY, EPSILON);
  }

  BOOST_FIXTURE_TEST_CASE(compShapeCopyOperator, fixture)
  {
    usanov::CompositeShape testCompositeShape = compShape;

    BOOST_CHECK_CLOSE(testCompositeShape.getArea(), compShape.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().height, compShape.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().width, compShape.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().pos.x, compShape.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().pos.y, compShape.getFrameRect().pos.y, EPSILON);
    BOOST_CHECK_EQUAL(testCompositeShape.getSize(), compShape.getSize());
  }

  BOOST_FIXTURE_TEST_CASE(compShapeMoveOperator, fixture)
  {
    const double originalArea = compShape.getArea();
    const double originalFrameHeight = compShape.getFrameRect().height;
    const double originalFrameWidth = compShape.getFrameRect().width;
    const double originalFramePosX = compShape.getFrameRect().pos.x;
    const double originalFramePosY = compShape.getFrameRect().pos.y;
    const size_t originalSize = compShape.getSize();
    usanov::CompositeShape testCompositeShape = std::move(compShape);

    BOOST_CHECK_CLOSE(testCompositeShape.getArea(), originalArea, EPSILON);
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().height, originalFrameHeight, EPSILON);
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().width, originalFrameWidth, EPSILON);
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().pos.x, originalFramePosX, EPSILON);
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().pos.y, originalFramePosY, EPSILON);
    BOOST_CHECK_EQUAL(testCompositeShape.getSize(), originalSize);

    BOOST_CHECK_EQUAL(compShape.getSize(), 0);
    BOOST_CHECK_THROW(compShape.getArea(), std::logic_error);
    BOOST_CHECK_THROW(compShape.remove(0), std::out_of_range);
    BOOST_CHECK_THROW(compShape.getFrameRect(), std::logic_error);
    BOOST_CHECK_THROW(compShape.move(-4.5, 5.0), std::logic_error);
    BOOST_CHECK_THROW(compShape.scale(5.0), std::logic_error);
  }

  BOOST_FIXTURE_TEST_CASE(compShapeWrongParameters, fixture)
  {
    usanov::CompositeShape emptyShape;
    BOOST_CHECK_THROW(emptyShape.getArea(), std::logic_error);
    BOOST_CHECK_THROW(emptyShape.scale(5.0), std::logic_error);
    BOOST_CHECK_THROW(emptyShape.scale(-200.0), std::invalid_argument);
    BOOST_CHECK_THROW(emptyShape.scale(5.0), std::logic_error);
    BOOST_CHECK_THROW(emptyShape.move(-200.0, 14.45), std::logic_error);
    BOOST_CHECK_THROW(emptyShape.getFrameRect(), std::logic_error);
    BOOST_CHECK_THROW(emptyShape.getArea(), std::logic_error);

    usanov::Circle testCircle(TEST_RAD, TEST_POS_CIRCLE2);
    std::shared_ptr<usanov::Shape> testCirclePtr = std::make_shared<usanov::Circle>(testCircle);
    compShape.append(testCirclePtr);
    BOOST_CHECK_THROW(compShape.append(nullptr), std::invalid_argument);
    BOOST_CHECK_THROW(compShape.append(testCirclePtr), std::invalid_argument);
    std::shared_ptr<usanov::CompositeShape> compShape2 = std::make_shared<usanov::CompositeShape>();
    BOOST_CHECK_THROW(compShape2->append(compShape2), std::logic_error);
  }

BOOST_AUTO_TEST_SUITE_END()
