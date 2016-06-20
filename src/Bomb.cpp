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

  Private(Bomb& s) : self(s), ticks(defaultTicks),
      radius(defaultRadius), alive(true) {};
  void detonate();

  Bomb& self;

  size_t ticks;
  size_t radius;

  bool alive;
};

const size_t Bomb::Private::defaultTicks = 100;
const size_t Bomb::Private::defaultRadius = 2;

Bomb::Bomb(Game& core, int id) : GameObject(core, id), d(new Private(*this)) {
}

Bomb::~Bomb() {}

int Bomb::print() const {
  return 'B';
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

void Bomb::onStackWith(int) {}

size_t Bomb::getRadius() const {
  return d->radius;
}

void Bomb::setRadius(size_t r) {
  d->radius = r;
}

void Bomb::Private::detonate() {
  SPtr<Engine> e = self.core.getEngine();
  Point t;

  alive = false; // Prevent recursive detonation.

  // Detonate in all directions.
  t = self.position;
  t.y += radius;
  e->explode(self.position, t);

  t = self.position;
  t.y -= radius;
  e->explode(self.position, t);

  t = self.position;
  t.x += radius;
  e->explode(self.position, t);

  t = self.position;
  t.x -= radius;
  e->explode(self.position, t);
}
