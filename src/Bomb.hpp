#ifndef BOMB_HPP
#define BOMB_HPP

#include "commons.hpp"
#include "GameObject.hpp"

class Game;

class Bomb : public GameObject {
public:
  Bomb(Game& core, int id);

  Bomb(const Bomb&) = delete;
  Bomb& operator =(const Bomb&) = delete;

  ~Bomb();

  int print() const;

  Point pos() const;
  bool move(const Point&);

  bool alive() const;
  bool kill();

  void update();

  size_t getRadius() const;
  void setRadius(size_t);
private:
  class Private;
  UPtr<Private> d;
};

#endif
