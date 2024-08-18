#ifndef HELPERS_HPP
#define HELPERS_HPP
#include <functional>

#include "figures.hpp"

namespace demin
{
  bool odd(const Polygon &p);
  bool even(const Polygon &p);
  bool checkVertexes(size_t count, const Polygon &p);
  bool compareAreas(const Polygon &p1, const Polygon &p2);
  bool compareVertexes(const Polygon &p1, const Polygon &p2);
  double getArea(const Polygon& points);

  struct AccumulateArea
  {
    demin::Point p1;
    double operator()(double& res, const demin::Point& p2, const demin::Point& p3)
    {
      res += 0.5 * (std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y)));
      p1 = p2;
      return res;
    }
  };
}
#endif
