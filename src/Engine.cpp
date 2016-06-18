#include "Engine.hpp"
#include "Game.hpp"

class Engine::Private {
public:
  Private(Game& c) : core(c), running(false),
      //Set default simulation parameters.
      mode(Engine::ModeSingle) {};

  Game& core;
  bool running;
  enum Engine::Mode mode;
};

Engine::Engine(Game& core) : d(new Private(core)) {}

Engine::~Engine() {}

bool Engine::isRunning() const {
  return d->running;
}

void Engine::run() {
  if (!d->running) {
    // TODO: Start simulation.
    d->running = true;
  }
}

void Engine::stop() {
  if (d->running) {
    // TODO: Stop simulation.
    d->running = false;
  }
}

void Engine::restart() {
  if (d->running) {
    stop();
  }

  run();
}

void Engine::update() {

}

enum Engine::Mode Engine::getMode() const {
  return d->mode;
}

void Engine::setMode(enum Mode m) {
  d->mode = m;
}
