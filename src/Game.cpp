#include <chrono>
#include <ncurses.h>
#include "Engine.hpp"
#include "Game.hpp"
#include "ObjectContainer.hpp"
#include "Level.hpp"
#include "Config.hpp"
#include "UI.hpp"

class Game::Private {
public:
  // Components.
  SPtr<ObjectContainer> gameObjects;
  SPtr<Config> config;
  SPtr<Engine> engine;
  SPtr<UI> ui;
  SPtr<Level> loadedLevel;

  bool isRunning;  

  // Controls loop speed.
  static const std::chrono::milliseconds updateMsec;
};

const std::chrono::milliseconds Game::Private::updateMsec = std::chrono::milliseconds(100);

Game::Game() : d(new Private()) {
  d->gameObjects.reset(new ObjectContainer());
  d->config.reset(new Config());
  d->engine.reset(new Engine(*this));
  d->ui.reset(new UI(*this));

  d->loadedLevel.reset(new Level(*this));
  d->isRunning = true;

}

Game::~Game() {}

void Game::update() {

  if (d->engine->isRunning()) {
    // Advance simulation to current time.
    
    d->engine->update();
  }

  // Render current screen.
  d->ui->update();
  // Discard symbol at keyboard input.
  getch();
}

bool Game::isRunning() const {
  return d->isRunning;
}

void Game::quit() {
  d->isRunning = false;
}

SPtr<Config> Game::getConfig() {
  return d->config;
}

const SPtr<Config> Game::getConfig() const {
  return d->config;
}

SPtr<Engine> Game::getEngine() {
  return d->engine;
}

const SPtr<Engine> Game::getEngine() const {
  return d->engine;
}

SPtr<Level> Game::getLevel() {
  return d->loadedLevel;
}

const SPtr<Level> Game::getLevel() const {
  return d->loadedLevel;
}

SPtr<ObjectContainer> Game::getObjects() {
  return d->gameObjects;
}

const SPtr<ObjectContainer> Game::getObjects() const {
  return d->gameObjects;
}

SPtr<UI> Game::getUI() {
  return d->ui;
}

const SPtr<UI> Game::getUI() const {
  return d->ui;
}
