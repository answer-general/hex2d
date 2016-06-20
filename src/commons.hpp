/*!
 * \file commons.hpp
 */
#ifndef COMMONS_HPP
#define COMMONS_HPP

#include <memory>

template <typename T>
using UPtr = std::unique_ptr<T>;

template <typename T>
using SPtr = std::shared_ptr<T>;

template <typename T>
using WPtr = std::weak_ptr<T>;
/*!
 * \struct Point
 * Contain point coordinates.
 */
struct Point {
  /*!
   * Constructor.
   * \memberof Point
   */
  Point(int nx = 0, int ny = 0) : x(nx), y(ny) {};
  /*!
   * Operator < overloading.
   * \memberof Point
   */
  bool operator <(const Point& o) const {
   return  (x < o.x) || (x == o.x && y < o.y); 
  };
  /*!
   * Operator == overloading.
   * \memberof Point
   */
  bool operator ==(const Point& o) const { return (!(*this < o) && !(o < *this)); };
  /*!
   * Operator != overloading.
   * \memberof Point
   */
  bool operator !=(const Point& o) const { return !(*this == o); };
  /*!
   * \var x
   * x coordinate
   * \memberof Point
   */
  int x;
  /*!
   * \var y
   * y coordinate
   * \memberof Point
   */
  int y;
};

#endif
