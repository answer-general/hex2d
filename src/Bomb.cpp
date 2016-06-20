#include "Bomb.hpp"
#include "Engine.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Level.hpp"
#include "ObjectContainer.hpp"

class Bomb::Private {
public:
  static const size_t defaultTicks;
  static const size_t defaultRadius;

  Private(Game& c) : core(c), ticks(defaultTicks),
      radius(defaultRadius), pos(-1,-1), alive(true) {};
  void detonate();

  Game& core;

  size_t ticks;
  size_t radius;

  Point pos;
  bool alive;
};

const size_t Bomb::Private::defaultTicks = 100;
const size_t Bomb::Private::defaultRadius = 2;

Bomb::Bomb(Game& core, int id) : GameObject(id), d(new Private(core)) {
}

Bomb::~Bomb() {}

int Bomb::print() const {
  return 'B';
}

Point Bomb::pos() const {
  return d->pos;
}

bool Bomb::move(const Point& p) {
  SPtr<Level> l = d->core.getLevel();

  if (d->alive && l->canCross(p)) {
    d->pos = p;
    return true;
  } else {
    return false;
  }
}

bool Bomb::alive() const {
  return d->alive;
}

bool Bomb::kill() {
  if (d->alive) { // Prevent recursive detonation.
    d->alive = false;
    d->detonate();
  }
  return true;
}

void Bomb::update() {
  --d->ticks;
  if (d->ticks == 0) {
    d->alive = false;
    d->detonate();
  }
}

size_t Bomb::getRadius() const {
  return d->radius;
}

void Bomb::setRadius(size_t r) {
  d->radius = r;
}

void Bomb::Private::detonate() {
  SPtr<Engine> e = core.getEngine();
  Point t;

  alive = false; // Prevent recursive detonation.

  // Detonate in all directions.
  t = pos;
  t.y += radius;
  e->explode(pos, t);

  t = pos;
  t.y -= radius;
  e->explode(pos, t);

  t = pos;
  t.x += radius;
  e->explode(pos, t);

  t = pos;
  t.x -= radius;
  e->explode(pos, t);
}
