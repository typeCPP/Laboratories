#include "circle.hpp"

#include <iostream>
#include <stdexcept>
#include <cmath>

Circle::Circle(double radius, const point_t &center):
  radius_(radius),
  center_(center)
{
  if (radius <= 0.0)
  {
    throw std::invalid_argument("wrong parameters");
  }
}

double Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, center_};
}

void Circle::move(const point_t &point)
{
  center_ = point;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
