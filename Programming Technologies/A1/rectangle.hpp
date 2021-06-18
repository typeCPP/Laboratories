#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(double width, double height, const point_t &center);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &point) override;
  void move(double dx, double dy) override;

private:
  double width_, height_;
  point_t center_;
};

#endif
