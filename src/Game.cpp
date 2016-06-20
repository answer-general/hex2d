#include <chrono>
#include <ncurses.h>
#include <thread>
#include <vector>
#include "Engine.hpp"
#include "Game.hpp"
#include "InputMethod.hpp"
#include "KeyboardInput.hpp"
#include "ObjectContainer.hpp"
#include "Level.hpp"
#include "Config.hpp"
#include "UI.hpp"

#include <fstream>

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

  int pcId;
};

const std::chrono::milliseconds Game::Private::updateMsec = std::chrono::milliseconds(50);

Game::Game() : d(new Private()) {
  d->gameObjects.reset(new ObjectContainer());
  d->config.reset(new Config());
  d->engine.reset(new Engine(*this));
  d->ui.reset(new UI(*this));

  d->loadedLevel.reset(new Level(*this));
  d->isRunning = true;

  d->pcId = GameObject::InvalidObject;
}

Game::~Game() {}

void Game::run() {
  std::chrono::system_clock::time_point prev;
  std::chrono::system_clock::time_point curr = std::chrono::system_clock::now();
  std::chrono::milliseconds lag(0);

  std::ofstream of("log.txt");

  while (isRunning()) {
    d->handleInput();

    if (d->engine->isRunning()) {
      prev = curr;
      curr = std::chrono::system_clock::now();

      lag += std::chrono::duration_cast<std::chrono::milliseconds>(curr - prev);

      // Advance simulation to current time.
      while (lag > d->updateMsec) {
        d->engine->update();
        lag -= d->updateMsec;

        if (d->pcId == GameObject::InvalidObject) { // Game over.
          d->engine->stop();
        }
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    of << std::chrono::duration_cast<std::chrono::milliseconds>(lag).count() << '\n';
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

int Game::getPCId() const {
  return d->pcId;
}

void Game::setPC(int id) {
  d->pcId = id;
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
