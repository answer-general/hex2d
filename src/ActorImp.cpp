#include "ActorImp.hpp"
#include "ActorMage.hpp"
#include "GameObject.hpp"
#include "Game.hpp"
#include "InputMethod.hpp"
#include "Level.hpp"
#include "ObjectContainer.hpp"
#include <stdexcept>

class ActorImp::Private {
public:
  static const int defaultSpeed = 1;

  Private(Game& c, ActorImp& s) : core(c), self(s), pos(-1, -1),
      alive(true), speed(defaultSpeed), tick(0) {};

  void onCmdMove(InputMethod::Command cmd);

  Game& core;
  ActorImp& self;

  Point pos;

  bool alive;
  int speed;
  int tick;
};

ActorImp::ActorImp(Game& core, int id) : Actor(id), d(new Private(core, *this)) {}

ActorImp::~ActorImp() {}

int ActorImp::print() const {
  return '@';
}

Point ActorImp::pos() const {
  return d->pos;
}

bool ActorImp::move(const Point& tgt) {
  SPtr<Level> l = d->core.getLevel();

  if (d->alive && l->canCross(tgt)) {
    d->pos = tgt;

    // Are there enemies?
    SPtr<ObjectContainer> objs = d->core.getObjects();
    std::vector<int> idsAt = objs->getIdsIn(d->pos, d->pos);

    // Pick all of them up.
    for (auto x : idsAt) {
      if (GameObject::idIsActor(x)) {
        // Kill only mages.
        try {
          SPtr<ActorMage> enemy = std::dynamic_pointer_cast<ActorMage>(
              objs->getObject(x));
          enemy->kill();
        } catch (const std::bad_cast&) {};
      }
    }

    return true;
  } else {
    return false;
  }

  return true;
}

bool ActorImp::alive() const {
  return d->alive;
}

bool ActorImp::kill() {
  if (d->alive) {
    d->alive = false;
    return true;
  }

  return false;
}
 
void ActorImp::update() {
  if (input) {
    InputMethod::Command cmd = input->getNextCommand();

    switch (cmd) {
    case InputMethod::MoveUp:
    case InputMethod::MoveDown:
    case InputMethod::MoveRight:
    case InputMethod::MoveLeft:
      d->onCmdMove(cmd);
      break;
    default:
      break;
    };
  }
}

void ActorImp::boostBombCount(int, int) {}

void ActorImp::boostBombRadius(int, int) {}

void ActorImp::boostInvul(int) {}

void ActorImp::boostSpeed(int, int) {}

void ActorImp::Private::onCmdMove(InputMethod::Command cmd) {
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
