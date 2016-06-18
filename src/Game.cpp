#include <ncurses.h>
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
  SPtr<UI> ui;
  SPtr<Level> loadedLevel;

  enum Game::State currentState;
};

Game::Game() : d(new Private()) {
  d->gameObjects.reset(new ObjectContainer());
  d->config.reset(new Config());
  d->ui.reset(new UI(*this));
}

Game::~Game() {}

void Game::update() {
  d->ui->update();
  
  // Discard symbol at keyboard input.
  getch();
}

bool Game::isRunning() const {
  return (d->currentState != State::GameStopped);
}

void Game::setState(enum State s) {
  d->currentState = s;
}

SPtr<Config> Game::getConfig() {
  return d->config;
}

const SPtr<Config> Game::getConfig() const {
  return d->config;
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
