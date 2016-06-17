#ifndef COMMONS_HPP
#define COMMONS_HPP

#include <memory>

template <typename T>
using UPtr = std::unique_ptr<T>;

template <typename T>
using SPtr = std::shared_ptr<T>;

template <typename T>
using WPtr = std::weak_ptr<T>;

struct Point {
  Point(size_t nx = 0, size_t ny = 0) : x(nx), y(ny) {};
  bool operator <(const Point& o) const { return (x < o.x) && (y < o.y); };
  bool operator ==(const Point& o) const { return (x == o.x) && (y == o.y); };
  size_t x;
  size_t y;
};

#endif
