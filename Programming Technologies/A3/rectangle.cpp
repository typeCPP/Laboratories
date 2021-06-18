#include "rectangle.hpp"

#include <iostream>
#include <stdexcept>

usanov::Rectangle::Rectangle(double width, double height, const point_t &center) :
  width_(width),
  height_(height),
  center_(center)
{
  if ((width <= 0.0) || (height <= 0.0))
  {
    throw std::invalid_argument("wrong parameters");
  }
}

double usanov::Rectangle::getArea() const
{
  return width_ * height_;
}

usanov::rectangle_t usanov::Rectangle::getFrameRect() const
{
  return {width_, height_, center_};
}

void usanov::Rectangle::move(const point_t &point)
{
  center_ = point;
}

void usanov::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void usanov::Rectangle::scale(double coefficient)
{
  if(coefficient <= 0)
  {
    throw std::invalid_argument("Wrong scaling coefficient");
  }
  width_ *= coefficient;
  height_ *= coefficient;
}

double usanov::Rectangle::getWidth() const
{
  return width_;
}

double usanov::Rectangle::getHeight() const
{
  return height_;
}
