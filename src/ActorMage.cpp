#include "ActorMage.hpp"
#include "Game.hpp"
#include "InputMethod.hpp"
#include "Level.hpp"

class ActorMage::Private {
public:
  const double defaultSpeed = 0.25;

  Private(Game& c, ActorMage& self) : core(c), self(self), 
      active(true), speed(defaultSpeed), tick(0) {};
  void move(InputMethod::Command cmd);

  Game& core;
  ActorMage& self;

  bool active;
  double speed;
  size_t tick;
};

ActorMage::ActorMage(Game& core, int id) : Actor(id),
    d(new Private(core, *this)) {}

ActorMage::~ActorMage() {}

void ActorMage::update() {
  // Get input and react.
  InputMethod::Command cmd;
  if (input)
    cmd = input->getNextCommand();
  else
    cmd = InputMethod::NoCommand;

  switch (cmd) {
  case InputMethod::MoveUp:
  case InputMethod::MoveRight:
  case InputMethod::MoveDown:
  case InputMethod::MoveLeft:
    d->move(cmd);
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

void ActorMage::Private::move(InputMethod::Command cmd) {
  // Slow character down.
  tick++;
  size_t move = (size_t)(speed * tick);
  if (move == 0)
    return;
  else
    tick = 0;

  SPtr<Level> level = core.getLevel();
  Point pos = level->getObjectPos(self.getId());

  switch (cmd) {
  case InputMethod::MoveUp:
    if (pos.y == 0)
      return;
    else if (pos.y < move)
      pos.y = 0;
    else
      pos.y -= move;
    break;
  case InputMethod::MoveLeft:
    if (pos.x == 0)
      return;
    else if (pos.x < move)
      pos.x = 0;
    else
      pos.x -= move;
    break;
  case InputMethod::MoveDown:
    if (pos.y == level->getSize().y)
      return;
    else if (pos.y + move > level->getSize().y)
      pos.y = level->getSize().y;
    else
      pos.y += move;
    break;
  case InputMethod::MoveRight:
    if (pos.x == level->getSize().x)
      return;
    else if (pos.x + move > level->getSize().x)
      pos.x = level->getSize().x;
    else
      pos.x += move;
    break;
  default: // Incorrect move.
    return;
  };

  level->moveTo(self.getId(), pos);
}
