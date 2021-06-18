#include <iostream>
#include <stdexcept>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
  const usanov::point_t circlePoint{11.5, -3.6};
  try
  {
    std::cout << "Creating circle with coordinates (11.5, -3.6) and radius 10.\n";
    usanov::Circle firstCircle(10.0, circlePoint);
    std::cout << "Area of the circle is " << firstCircle.getArea() << "\n";
    firstCircle.scale(2.0);
    std::cout << "Area of the circle after scaling by 2 is " << firstCircle.getArea() << "\n";
    firstCircle.scale(0.5);
    std::cout << "Area of the circle after scaling by 0.5 is " << firstCircle.getArea() << "\n";
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }

  const usanov::point_t rectanglePoint{13.5, -7.4};
  try
  {
    std::cout << "\nCreating rectangle with coordinates (13.5, -7.4), height 5 and width 10.\n";
    usanov::Rectangle firstRectangle(10.0, 5.0, rectanglePoint);
    std::cout << "Area of the rectangle is " << firstRectangle.getArea() << "\n";
    firstRectangle.scale(3.0);
    std::cout << "Area of the rectangle after scaling by 3 is " << firstRectangle.getArea() << "\n";
    firstRectangle.scale(0.5);
    std::cout << "Area of the rectangle after scaling by 0.5 is " << firstRectangle.getArea() << "\n";
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }
  const usanov::point_t compPoint1{13.5, -11.0};
  const usanov::point_t compPoint2{13.5, 9.0};
  const usanov::point_t compPoint3{30.0, 40.0};
  try
  {
    std::cout << "\nCreating two rectangles with width 10 and height 20.";
    usanov::Rectangle firstRect(10, 20, compPoint1);
    usanov::Rectangle secondRect(10, 20, compPoint2);
    std::shared_ptr<usanov::Shape> firstRectPtr = std::make_shared<usanov::Rectangle>(firstRect);
    std::shared_ptr<usanov::Shape> secondRectPtr = std::make_shared<usanov::Rectangle>(secondRect);
    std::cout << "\nCoordinates of the first rectangle = (" << firstRect.getFrameRect().pos.x << ", "
              << firstRect.getFrameRect().pos.y << ")"
              << "\nCoordinates of the second rectangle = (" << secondRect.getFrameRect().pos.x << ", "
              << secondRect.getFrameRect().pos.y << ")";
    usanov::CompositeShape compShape;
    std::cout << "\nAdding both to the new composite shape.";
    compShape.append(firstRectPtr);
    compShape.append(secondRectPtr);
    std::cout << "\nArea of the composite shape: " << compShape.getArea()
              << "\nCenter of the composite shape = (" << compShape.getFrameRect().pos.x << ", "
              << compShape.getFrameRect().pos.y << ")";
    compShape.scale(2.0);
    std::cout << "\nArea of the composite shape after scaling it by 2: " << compShape.getArea()
              << "\nCenter of the composite shape after scaling it by 2 = (" << compShape.getFrameRect().pos.x << ", "
              << compShape.getFrameRect().pos.y << ")";
    compShape.move(10, 10);
    std::cout << "\nCenter of the composite shape after moving by 10,10 = (" << compShape.getFrameRect().pos.x << ", "
              << compShape.getFrameRect().pos.y << ")";
    compShape.move(compPoint3);
    std::cout << "\nCenter after moving on point(30, 40) = (" << compShape.getFrameRect().pos.x << ", "
              << compShape.getFrameRect().pos.y << ")\n"
              << "Size of composite shape is " << compShape.getSize() << "\n"
              << "First element area is " << compShape[0]->getArea() << "\n"
              << "Second element area is " << compShape[1]->getArea() << "\n";
    usanov::CompositeShape compShape2(compShape);
    std::cout << "\nChecking size of copied composite shape.\n"
              << "Size is " << compShape2.getSize() << "\n"
              << "Checking area of copied composite shape.\n"
              << "Area is " << compShape2.getArea() << "\n";
    usanov::CompositeShape compShape3(std::move(compShape2));
    std::cout << "\nChecking size of moved composite shape from previous.\n"
              << "Size is " << compShape3.getSize() << "\n"
              << "Checking area of moved composite shape.\n"
              << "Area is " << compShape3.getArea() << "\n";
    compShape.remove(0);
    std::cout << "Area of composite shape after deleting first element: " << compShape.getArea();
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }
  return 0;
}
