#include "shape.hpp"
#include <cmath>
#include <iterator>
#include "utility.hpp"

const char OPENING_BRACKET = '(';
const char SEMICOLON = ';';
const char CLOSING_BRACKET = ')';

const size_t SIZE_OF_TRIANGLE = 3;
const size_t SIZE_OF_RECTANGLE = 4;
const size_t SIZE_OF_PENTAGON = 5;

std::istream &operator>>(std::istream &input, Point &point)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  StreamGuard streamGuard(input);
  input >> std::noskipws;
  char currentSymbol;
  input >> skipWs >> currentSymbol;
  if (!input)
  {
    return input;
  }
  if (currentSymbol != OPENING_BRACKET)
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  Point tempPoint{};
  input >> skipWs >> tempPoint.x >> skipWs >> currentSymbol;
  if (!input)
  {
    return input;
  }
  if (currentSymbol != SEMICOLON)
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  input >> skipWs >> tempPoint.y >> skipWs >> currentSymbol;
  if (!input)
  {
    return input;
  }
  if (currentSymbol != CLOSING_BRACKET)
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  point.x = tempPoint.x;
  point.y = tempPoint.y;
  return input;
}

std::ostream &operator<<(std::ostream &output, const Point &point)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  output << OPENING_BRACKET << point.x << SEMICOLON << point.y << CLOSING_BRACKET;
  return output;
}

std::istream &operator>>(std::istream &input, Shape &shape)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  StreamGuard streamGuard(input);
  input >> std::noskipws;

  size_t numOfVertexes;
  input >> skipWs >> numOfVertexes;
  if (!input)
  {
    return input;
  }
  if (numOfVertexes == 0)
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  Shape tempShape;
  for (size_t i = 0; i < numOfVertexes; i++)
  {
    Point pointToRead{};
    input >> pointToRead;
    if (input.fail())
    {
      return input;
    }
    tempShape.push_back(pointToRead);
  }
  input >> skipWs;
  if (input.eof() || (input.peek() == '\n'))
  {
    shape = std::move(tempShape);
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::ostream &operator<<(std::ostream &output, const Shape &shape)
{
  std::ostream::sentry sentry(output);
  if (sentry)
  {
    output << shape.size() << " ";
    std::copy(shape.begin(), shape.end(), std::ostream_iterator<Point>(output, " "));
  }
  return output;
}

size_t getSquaredDistance(const Point &point1, const Point &point2)
{
  return (point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y);
}

bool isTriangle(const Shape &shape)
{
  return shape.size() == SIZE_OF_TRIANGLE;
}

bool isRectangle(const Shape &shape)
{
  if (shape.size() != SIZE_OF_RECTANGLE)
  {
    return false;
  }
  return getSquaredDistance(shape[0], shape[1]) == getSquaredDistance(shape[2], shape[3])
      && getSquaredDistance(shape[1], shape[2]) == getSquaredDistance(shape[0], shape[3])
      && getSquaredDistance(shape[1], shape[3]) == getSquaredDistance(shape[0], shape[2]);
}

bool isSquare(const Shape &shape)
{
  if ((shape.size() != SIZE_OF_RECTANGLE) || (!isRectangle(shape)))
  {
    return false;
  }
  return getSquaredDistance(shape[0], shape[1]) == getSquaredDistance(shape[1], shape[2]);
}

bool isPentagon(const Shape &shape)
{
  return shape.size() == SIZE_OF_PENTAGON;
}

bool ShapesComparator::operator()(const Shape &shape1, const Shape &shape2) const
{
  if (isRectangle(shape1) && isRectangle(shape2))
  {
    if (isSquare(shape1) && !isSquare(shape2))
      return true;
  }
  return shape1.size() < shape2.size();
}
