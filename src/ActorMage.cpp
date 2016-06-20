#include <vector>
#include "ActorMage.hpp"
#include "Bomb.hpp"
#include "Game.hpp"
#include "InputMethod.hpp"
#include "ObjectContainer.hpp"
#include "Level.hpp"

class ActorMage::Private {
public:
  static const size_t defaultSpeed;
  static const size_t defaultBombRadius;
  static const size_t defaultBombCount;

  Private(Game& c, ActorMage& self) : core(c), self(self),
      speed(defaultSpeed), bombRadius(defaultBombRadius),
      bombCount(defaultBombCount), bonusSpeedLeft(0),
      bonusBombRadiusLeft(0), bonusBombCountLeft(0),
      bonusInvulLeft(0), alive(true), mortal(true),
      bombs(), pos(-1,-1) {};

  void checkBombs();
  void checkBoosts();
  void onCmdMove(InputMethod::Command cmd);
  void onCmdPlant();

  Game& core;
  ActorMage& self;

  double speed;
  size_t bombRadius;
  size_t bombCount;

  // Counters for bonuses.
  int bonusSpeedLeft;
  int bonusBombRadiusLeft;
  int bonusBombCountLeft;
  int bonusInvulLeft;

  bool alive;
  bool mortal;
  int tick; // For speed adjustments.
  std::vector< SPtr<Bomb> > bombs;

  Point pos;
};

const size_t ActorMage::Private::defaultSpeed = 1;
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
  d->checkBoosts();

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

void ActorMage::boostBombCount(int newCount, int durationTicks) {
  d->bonusBombCountLeft = durationTicks;
  d->bombCount = newCount;
}

void ActorMage::boostBombRadius(int newVal, int durationTicks) {
  d->bonusBombRadiusLeft = durationTicks;
  d->bombRadius = newVal;
}

void ActorMage::boostInvul(int durationTicks) {
  d->bonusInvulLeft = durationTicks;
  d->mortal = false;
}

void ActorMage::boostSpeed(int newVal, int durationTicks) {
  d->bonusSpeedLeft = durationTicks;
  d->speed = newVal;
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

void ActorMage::Private::checkBoosts() {
  if (--bonusBombCountLeft == 0)
    bombCount = defaultBombCount;
  if (--bonusBombRadiusLeft == 0)
    bombRadius = defaultBombRadius;
  if (--bonusInvulLeft == 0)
    mortal = true;
  if (--bonusSpeedLeft == 0)
    speed = defaultSpeed;
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
  if (bombs.size() >= bombCount)
    return;

  SPtr<Bomb> b(new Bomb(core, GameObject::genBombId()));
  b->setRadius(bombRadius);
  b->move(pos);

  core.getObjects()->addObject(b);
  bombs.push_back(b);
}
