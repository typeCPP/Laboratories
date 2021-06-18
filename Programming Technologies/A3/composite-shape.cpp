#include "composite-shape.hpp"

#include <memory>
#include <algorithm>
#include <stdexcept>
#include "base-types.hpp"

usanov::CompositeShape::CompositeShape(const usanov::CompositeShape &obj) :
  size_(obj.size_)
{
  if (obj.size_ > 0)
  {
    shapes_ = std::make_unique<std::shared_ptr<Shape>[]>(obj.size_);
    for (size_t s = 0; s < obj.size_; s++)
    {
      shapes_[s] = obj.shapes_[s];
    }
  }
}

double usanov::CompositeShape::getArea() const
{
  if (size_ == 0)
  {
    throw std::logic_error("Composite shape is empty");
  }
  double sum = 0.0;
  for (size_t i = 0; i < size_; i++)
  {
    sum += shapes_[i]->getArea();
  }
  return sum;
}

usanov::rectangle_t usanov::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    throw std::logic_error("Composite shape is empty");
  }
  rectangle_t shapeRect = shapes_[0]->getFrameRect();
  double leftestSide = shapeRect.pos.x - shapeRect.width / 2;
  double rightestSide = shapeRect.pos.x + shapeRect.width / 2;
  double highestSide = shapeRect.pos.y + shapeRect.height / 2;
  double lowestSide = shapeRect.pos.y - shapeRect.height / 2;
  for (size_t i = 1; i < size_; i++)
  {
    shapeRect = shapes_[i]->getFrameRect();
    leftestSide = std::min(shapeRect.pos.x - shapeRect.width / 2, leftestSide);
    rightestSide = std::max(shapeRect.pos.x + shapeRect.width / 2, rightestSide);
    highestSide = std::max(shapeRect.pos.y + shapeRect.height / 2, highestSide);
    lowestSide = std::min(shapeRect.pos.y - shapeRect.height / 2, lowestSide);
  }
  return rectangle_t{(rightestSide - leftestSide), (highestSide - lowestSide),
      {(rightestSide + leftestSide) / 2.0, (highestSide + lowestSide) / 2.0}};
}

void usanov::CompositeShape::move(const point_t &point)
{
  const rectangle_t frameRect = getFrameRect();
  move(point.x - frameRect.pos.x, point.y - frameRect.pos.y);
}

void usanov::CompositeShape::move(double dx, double dy)
{
  if (size_ == 0)
  {
    throw std::logic_error("Composite shape is empty");
  }
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i]->move(dx, dy);
  }
}

void usanov::CompositeShape::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Wrong scaling coefficient");
  }
  if (size_ == 0)
  {
    throw std::logic_error("Composite shape is empty");
  }
  const point_t centre = getFrameRect().pos;
  for (size_t i = 0; i < size_; i++)
  {
    const double xCoord = centre.x + coefficient * (shapes_[i]->getFrameRect().pos.x - centre.x);
    const double yCoord = centre.y + coefficient * (shapes_[i]->getFrameRect().pos.y - centre.y);
    shapes_[i]->move({xCoord, yCoord});
    shapes_[i]->scale(coefficient);
  }
}

void usanov::CompositeShape::append(const std::shared_ptr<Shape> &obj)
{
  if (obj == nullptr)
  {
    throw std::invalid_argument("Shape is empty");
  }
  if (obj.get() == this)
  {
    throw std::logic_error("Adding composite shape to itself");
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> newArray(new std::shared_ptr<Shape>[size_ + 1]);
  for (size_t i = 0; i < size_; i++)
  {
    if (shapes_[i].get() == obj.get())
    {
      throw std::invalid_argument("Composite shape contains this shape");
    }
    newArray[i] = shapes_[i];
  }
  newArray[size_] = obj;
  size_++;
  shapes_ = std::move(newArray);
}

void usanov::CompositeShape::remove(size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("Array index out of range");
  }
  for (size_t i = index; i < size_ - 1; i++)
  {
    shapes_[i] = std::move(shapes_[i + 1]);
  }
  size_--;
}

double usanov::CompositeShape::getSize() const
{
  return size_;
}

std::shared_ptr<usanov::Shape> usanov::CompositeShape::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("Array index out of range");
  }
  return shapes_[index];
}

usanov::CompositeShape::CompositeShape() :
  size_(0)
{}

usanov::CompositeShape::CompositeShape(usanov::CompositeShape &&src) noexcept:
  size_(src.size_),
  shapes_(std::move(src.shapes_))
{
  src.size_ = 0;
}

usanov::CompositeShape &usanov::CompositeShape::operator=(const usanov::CompositeShape &src)
{
  if (this == &src)
  {
    return *this;
  }
  if(src.size_ == 0)
  {
    size_ = 0;
    shapes_.reset();
  }
  shapes_ = std::make_unique<std::shared_ptr<Shape>[]>(src.size_);
  size_ = src.size_;
  for (size_t i = 0; i < src.size_; i++)
  {
    shapes_[i] = src.shapes_[i];
  }
  return *this;
}

usanov::CompositeShape &usanov::CompositeShape::operator=(usanov::CompositeShape &&src) noexcept
{
  if (this == &src)
  {
    return *this;
  }
  size_ = src.size_;
  src.size_ = 0;
  shapes_ = std::move(src.shapes_);
  return *this;
}
