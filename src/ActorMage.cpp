#include "ActorMage.hpp"
#include "Game.hpp"
#include "InputMethod.hpp"
#include "Level.hpp"

class ActorMage::Private {
public:
  Private(Game& c) : core(c), active(true) {};

  Game& core;

  bool active;
};

ActorMage::ActorMage(Game& core, int id) : Actor(id), d(new Private(core)) {}

ActorMage::~ActorMage() {}

void ActorMage::update() {
  SPtr<Level> level = d->core.getLevel();
  Point currentPos = level->getObjectPos(id);

  // Get input and react.
  InputMethod::Command cmd;
  if (input)
    cmd = input->getNextCommand();
  else
    cmd = InputMethod::NoCommand;

  switch (cmd) {
  case InputMethod::MoveUp:
    if (currentPos.y > 0)
      --currentPos.y;
    level->moveTo(id, currentPos);
    break;
  case InputMethod::MoveRight:
    ++currentPos.x;
    level->moveTo(id, currentPos);
    break;
  case InputMethod::MoveDown:
    ++currentPos.y;
    level->moveTo(id, currentPos);
    break;
  case InputMethod::MoveLeft:
    if (currentPos.x > 0)
      --currentPos.x;
    level->moveTo(id, currentPos);
    break;
  case InputMethod::BombPlant:
    break;
  case InputMethod::NoCommand:
  default:
    break;
  };
}

void ActorMage::explode() {

}

bool ActorMage::isActive() const {
  return d->active;
}
