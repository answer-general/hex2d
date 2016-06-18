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

  int getObjectAt(const Point& pos) const;

  bool spawn(int objId);
  bool moveTo(int id, const Point& pos);

  bool placeAt(int id, const Point& pos);

  bool fromFile(const std::string& name);
  void reset();
private:
  class Private;
  UPtr<Private> d;
};

#endif
