#ifndef A3_BASE_TYPES_HPP
#define A3_BASE_TYPES_HPP
namespace usanov
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };
}
#endif
