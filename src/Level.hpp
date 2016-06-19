#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "commons.hpp"
#include <string>

class Game;

class Cell {
public:
  Cell();

  Cell(const Cell& o);
  Cell& operator =(const Cell& o);

  size_t size() const;
  void clear();

  /// /return false if empty.
  bool back(int& id) const;
  /// /return false if empty.
  bool pop();
  /// /return false if full.
  bool push(int id);

  /// Searches for element inside.
  /// /return -1 if id not found.
  int find(int id) const;
  bool erase(size_t idx);
private:
  static const size_t MaxObjects = 16;

  int buffer[MaxObjects];
  size_t used;
};

class Level {
public:
  Level(Game& core);

  Level(const Level&) = delete;
  Level& operator =(const Level&) = delete;

  ~Level();

  const Point& getSize() const;

  int getTopObjectAt(const Point& pos) const;
  Cell getCellAt(const Point& pos) const;

  Point getObjectPos(int id) const;

  bool spawn(int objId);
  bool moveTo(int id, const Point& pos);

  bool placeAt(int id, const Point& pos);
  bool placeAt(const Cell& group, const Point& pos);

  bool fromFile(const std::string& name);
  void reset();
private:
  class Private;
  UPtr<Private> d;
};

#endif
