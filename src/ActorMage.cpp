#include "ActorMage.hpp"
#include "Game.hpp"
#include "InputMethod.hpp"

class ActorMage::Private {
public:
  Private(Game& c) : core(c) {};

  Game& core;
};

ActorMage::ActorMage(Game& core, int id) : Actor(id), d(new Private(core)) {}

ActorMage::~ActorMage() {}

void ActorMage::update() {
  // Get input and react.
  auto cmd = input->getNextCommand();

  switch (cmd) {
  case InputMethod::MoveUp:
    break;
  case InputMethod::MoveRight:
    break;
  case InputMethod::MoveDown:
    break;
  case InputMethod::MoveLeft:
    break;
  case InputMethod::BombPlant:
    break;
  default:
    break;
  };
}
