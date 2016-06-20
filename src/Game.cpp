#include <chrono>
#include <ncurses.h>
#include <thread>
#include <vector>
#include "Engine.hpp"
#include "Game.hpp"
#include "InputMethod.hpp"
#include "KeyboardInput.hpp"
#include "AIInput.hpp"
#include "ObjectContainer.hpp"
#include "Level.hpp"
#include "Config.hpp"
#include "UI.hpp"

class Game::Private {
public:
  void handleInput();

  // Components.
  SPtr<ObjectContainer> gameObjects;
  SPtr<Config> config;
  SPtr<Engine> engine;
  SPtr<UI> ui;
  SPtr<Level> loadedLevel;

  std::vector< SPtr<InputMethod> > inputs;

  bool isRunning;  

  // Controls loop speed.
  static const std::chrono::milliseconds updateMsec;

  int pc1Id;
  int pc2Id;
};

const std::chrono::milliseconds Game::Private::updateMsec = std::chrono::milliseconds(50);

Game::Game() : d(new Private()) {
  d->gameObjects.reset(new ObjectContainer());
  d->config.reset(new Config(*this));
  d->engine.reset(new Engine(*this));
  d->ui.reset(new UI(*this));

  d->loadedLevel.reset(new Level(*this));
  d->isRunning = true;

  d->pc1Id = GameObject::InvalidObject;
  d->pc2Id = GameObject::InvalidObject;
}

Game::~Game() {}

void Game::run() {
  std::chrono::system_clock::time_point prev;
  std::chrono::system_clock::time_point curr = std::chrono::system_clock::now();
  std::chrono::milliseconds lag(0);

  while (isRunning()) {
    d->handleInput();

    if (d->engine->isRunning()) {
      prev = curr;
      curr = std::chrono::system_clock::now();

      lag += std::chrono::duration_cast<std::chrono::milliseconds>(curr - prev);

      // Advance simulation to current time.
      while (d->engine->isRunning() && lag > d->updateMsec) {
        d->engine->update();
        lag -= d->updateMsec;

        if (d->pc1Id == GameObject::InvalidObject &&
            d->pc2Id == GameObject::InvalidObject) { // Game over.
          d->engine->stop();
        }
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // Render current screen.
    d->ui->update();
    // Discard symbol at keyboard input.
    getch();
  }
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

SPtr<InputMethod> Game::newKbdInput() {
  SPtr<InputMethod> res(new KeyboardInput(*this));

  d->inputs.push_back(res);

  return res;
}

SPtr<InputMethod> Game::newAIInput() {
  SPtr<InputMethod> res(new AIInput(*this));

  d->inputs.push_back(res);

  return res;
}

int Game::getPlayer1Id() const {
  return d->pc1Id;
}

void Game::setPlayer1(int id) {
  d->pc1Id = id;
}

int Game::getPlayer2Id() const {
  return d->pc2Id;
}

void Game::setPlayer2(int id) {
  d->pc2Id = id;
}

void Game::Private::handleInput() {
  for (auto it = inputs.begin(); it != inputs.end(); ++it) {
    // Delete unneeded inputs.
    if ((*it)->getTarget() == GameObject::InvalidObject) {
      it = inputs.erase(it);
      if (it == inputs.end()) // Check for last element.
        break;
    } else {
      (*it)->update();
    }
  }
}
