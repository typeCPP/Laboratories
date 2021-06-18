#ifndef A3_COMPOSITE_SHAPE_HPP
#define A3_COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace usanov
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape &obj);
    CompositeShape(CompositeShape &&src) noexcept;
    ~CompositeShape() = default;
    CompositeShape &operator=(const CompositeShape &src);
    CompositeShape &operator=(CompositeShape &&src) noexcept;
    std::shared_ptr<Shape> operator[](size_t index) const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &point) override;
    void move(double dx, double dy) override;
    void scale(double coefficient) override;
    void append(const std::shared_ptr<Shape> &);
    void remove(size_t index);
    double getSize() const;
  private:
    size_t size_;
    std::unique_ptr<std::shared_ptr<Shape>[]> shapes_;
  };
}

#endif
