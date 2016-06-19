#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "commons.hpp"
#include <string>

class Game;

class Level {
public:
  Level(Game& core);

  Level(const Level&) = delete;
  Level& operator =(const Level&) = delete;

  ~Level();

  const Point& getSize() const;

  /// /return Point(-1,-1) if no places left.
  Point nextSpawn();

  /// /return true if object was destroyed.
  bool destroy(const Point& pos);
  /// /return true if there is no wall at pos.
  bool canCross(const Point& pos);

  /// /return symbol code for the poins.
  int print(const Point& pos);

  bool fromFile(const std::string& name);
private:
  class Private;
  UPtr<Private> d;
};

#endif
