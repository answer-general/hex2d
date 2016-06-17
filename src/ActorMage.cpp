#include "ActorMage.hpp"
#include "Game.hpp"

class ActorMage::Private {
public:
  Private(Game& c) : core(c) {};

  Game& core;
};

ActorMage::ActorMage(Game& core, int id) : Actor(id), d(new Private(core)) {}

ActorMage::~ActorMage() {}

void ActorMage::update() {
  // Get input and react.
}
