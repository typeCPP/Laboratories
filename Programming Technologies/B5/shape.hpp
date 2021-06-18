#ifndef B5_SHAPE_HPP
#define B5_SHAPE_HPP

#include <iostream>
#include <vector>

struct Point
{
  int x;
  int y;
};

using Shape = std::vector<Point>;

struct ShapesComparator
{
  bool operator ()(const Shape &shape1, const Shape &shape2) const;
};

std::istream &operator>>(std::istream &input, Point &point);
std::ostream &operator<<(std::ostream &output, const Point &point);

std::istream &operator>>(std::istream &input, Shape &shape);
std::ostream &operator<<(std::ostream &output, const Shape &shape);

size_t getSquaredDistance(const Point &point1, const Point &point2);
bool isTriangle(const Shape &shape);
bool isRectangle(const Shape &shape);
bool isSquare(const Shape &shape);
bool isPentagon(const Shape &shape);

#endif
