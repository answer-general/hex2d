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
  static const double defaultSpeed;

  Private(ActorImp& s) : self(s), alive(true),
      speed(defaultSpeed), tick(0) {};

  void onCmdMove(InputMethod::Command cmd);

  ActorImp& self;

  bool alive;
  int speed;
  int tick;
};

const double ActorImp::Private::defaultSpeed = 0.5;

ActorImp::ActorImp(Game& core, int id) : Actor(core, id), d(new Private(*this)) {}

ActorImp::~ActorImp() {}

int ActorImp::print() const {
  return '@';
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

void ActorImp::onStackWith(int id) {
  // Kill enemies.
  if (GameObject::idIsActor(id)) {
    // Kill only mages.
    try {
      SPtr<ActorMage> enemy = std::dynamic_pointer_cast<ActorMage>(
          core.getObjects()->getObject(id));
      enemy->kill();
    } catch (const std::bad_cast&) {}; // Not a mage, ignore.
  }
}

void ActorImp::Private::onCmdMove(InputMethod::Command cmd) {
  int delta = (speed * (++tick));
  if (delta == 0)
    return;
  else
    tick = 0;

  Point p = self.position;

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
