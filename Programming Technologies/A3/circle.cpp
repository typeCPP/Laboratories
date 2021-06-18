#include "circle.hpp"

#include <iostream>
#include <stdexcept>
#include <cmath>

usanov::Circle::Circle(double radius, const point_t &center) :
  radius_(radius),
  center_(center)
{
  if (radius <= 0.0)
  {
    throw std::invalid_argument("wrong parameters");
  }
}

double usanov::Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

usanov::rectangle_t usanov::Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, center_};
}

void usanov::Circle::move(const point_t &point)
{
  center_ = point;
}

void usanov::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void usanov::Circle::scale(double coefficient)
{
  if(coefficient <= 0)
  {
    throw std::invalid_argument("Wrong scaling coefficient");
  }
  radius_ *= coefficient;
}

double usanov::Circle::getRadius() const
{
  return radius_;
}
