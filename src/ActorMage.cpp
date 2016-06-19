#include <vector>
#include "ActorMage.hpp"
#include "Bomb.hpp"
#include "Game.hpp"
#include "InputMethod.hpp"
#include "ObjectContainer.hpp"
#include "Level.hpp"

class ActorMage::Private {
public:
  static const double defaultSpeed;
  static const size_t defaultBombRadius;
  static const size_t defaultBombCount;

  Private(Game& c, ActorMage& self) : core(c), self(self),
      speed(defaultSpeed), bombRadius(defaultBombRadius),
      bombCount(defaultBombCount), alive(true), mortal(true),
      bombs(), pos(-1,-1) {};

  void checkBombs();
  void onCmdMove(InputMethod::Command cmd);
  void onCmdPlant();

  Game& core;
  ActorMage& self;

  double speed;
  size_t bombRadius;
  size_t bombCount;

  bool alive;
  bool mortal;
  int tick; // For speed adjustments.
  std::vector< SPtr<Bomb> > bombs;

  Point pos;
};

const double ActorMage::Private::defaultSpeed = 0.5;
const size_t ActorMage::Private::defaultBombRadius = 2;
const size_t ActorMage::Private::defaultBombCount = 1;

ActorMage::ActorMage(Game& core, int id) : Actor(id),
    d(new Private(core, *this)) {}

ActorMage::~ActorMage() {}

int ActorMage::print() const {
  return '$';
}

Point ActorMage::pos() const {
  return d->pos;
}

bool ActorMage::move(const Point& tgt) {
  SPtr<Level> l = d->core.getLevel();

  if (d->alive && l->canCross(tgt)) {
    d->pos = tgt;
    return true;
  } else {
    return false;
  }
}

bool ActorMage::alive() const {
  return d->alive;
}

bool ActorMage::kill() {
  if (d->mortal) {
    d->alive = false;
    return true;
  } else {
    return false;
  }
}
 
void ActorMage::update() {
  d->checkBombs();

  if (input) {
    InputMethod::Command cmd = input->getNextCommand();

    switch (cmd) {
    case InputMethod::MoveUp:
    case InputMethod::MoveDown:
    case InputMethod::MoveRight:
    case InputMethod::MoveLeft:
      d->onCmdMove(cmd);
      break;
    case InputMethod::BombPlant:
      d->onCmdPlant();
      break;
    default:
      break;
    }
  }
}

void ActorMage::Private::checkBombs() {
  for (auto it = bombs.begin(); it != bombs.end(); ++it) {
    if (!((*it)->alive())) {
      it = bombs.erase(it);
      if (it == bombs.end())
        break;
    }
  }
}

void ActorMage::Private::onCmdMove(InputMethod::Command cmd) {
  int delta = (speed * (tick++));
  if (delta == 0)
    return;
  else
    tick = 0;

  Point p = pos;

  switch (cmd) {
  case InputMethod::MoveUp:
    --p.y;
    break;
  case InputMethod::MoveDown:
    ++p.y;
    break;
  case InputMethod::MoveLeft:
    --p.x;
    break;
  case InputMethod::MoveRight:
    ++p.x;
    break;
  default:
    return;
    break;
  };

  self.move(p);
}

void ActorMage::Private::onCmdPlant() {
  if (bombs.size() == bombCount)
    return;

  SPtr<Bomb> b(new Bomb(core, GameObject::genBombId()));
  b->setRadius(bombRadius);
  b->move(pos);

  core.getObjects()->addObject(b);
  bombs.push_back(b);
}
