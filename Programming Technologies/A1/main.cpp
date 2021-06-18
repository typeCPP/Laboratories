#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  const point_t circlePoint1{65.5, 70.0};
  try
  {
    Circle firstCircle(10.0, circlePoint1);
    std::cout << "Square of the first circle with coordinates (65.5, 70.0) and radius 10.0: " << firstCircle.getArea()
              << std::endl;
    std::cout << "Width and height of frame rectangle for circle: " << firstCircle.getFrameRect().width << ", "
              << firstCircle.getFrameRect().height << "\n";
    std::cout << "Center of frame rectangle for circle (" << firstCircle.getFrameRect().pos.x << ", "
              << firstCircle.getFrameRect().pos.y << ")\n";
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }

  const point_t rectPoint1{-100.0, 55.0};
  try
  {
    Rectangle firstRect(100, 200, rectPoint1);
    std::cout << "\nSquare of the first rectangle with coordinates (-100.0, 55.0) and width 100, height 200: "
              << firstRect.getArea() << std::endl;

    std::cout << "\nCircle has coordinates of center (" << circlePoint1.x << ", " << circlePoint1.y << ")";
    std::cout << "\nRectangle has coordinates of center (" << rectPoint1.x << ", " << rectPoint1.y << ")\n";
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }
  try
  {
    std::cout << "\nTrying to create a new circle with radius 5.0";
    Circle secondCircle(5.0, circlePoint1);
    std::cout << "\nCircle has coordinates of center (" << circlePoint1.x << ", " << circlePoint1.y << ")";
    std::cout << "\nSquare is " << secondCircle.getArea() << std::endl;
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }

  const point_t circlePoint3{50.0, 30.0};
  try
  {
    std::cout << "\nCreating a third circle with radius 15 and using polymorphic way for next actions with it.";
    Circle thirdCircle(15, circlePoint3);
    Shape *shape = &thirdCircle;
    std::cout << "\nArea of third circle is: " << shape->getArea();
    std::cout << "\nCoordinates of the circle (" << circlePoint3.x << ", " << circlePoint3.y << ")";
    shape->move(30, 30);
    std::cout << "\nCoordinates of the circle after moving (" << shape->getFrameRect().pos.x << ", "
              << shape->getFrameRect().pos.y << ")";
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }
  return 0;
}
