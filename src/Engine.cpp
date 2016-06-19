#include <string>
#include <vector>
#include "ActorMage.hpp"
#include "Engine.hpp"
#include "Game.hpp"
#include "ObjectContainer.hpp"
#include "GameObject.hpp"
#include "Level.hpp"

class Engine::Private {
public:
  static const enum Engine::Mode defaultMode;
  Private(Game& c) : core(c), running(false),
      mode(defaultMode), levelName() {};

  void setupSingle();
  void setupHotseat();
  void setupMulti();

  bool detonateCell(const Point&);

  Game& core;

  bool running;
  enum Engine::Mode mode;

  std::string levelName;
};

const enum Engine::Mode Engine::Private::defaultMode = Engine::ModeSingle;

Engine::Engine(Game& core) : d(new Private(core)) {
}

Engine::~Engine() {}

bool Engine::isRunning() const {
  return d->running;
}

void Engine::run() {
  if (d->levelName == "")
    return;

  d->core.getLevel()->fromFile(d->levelName);

  switch (d->mode) {
  case ModeSingle:
    d->setupSingle();
    break;
  case ModeHotseat:
    d->setupHotseat();
    break;
  case ModeMulti:
    d->setupMulti();
    break;
  default:
    return;
    break;
  };

  d->running = true;
}

void Engine::stop() {
  d->core.getObjects()->clear();
  d->running = false;
}

void Engine::update() {
  SPtr<ObjectContainer> objs = d->core.getObjects();

  // Discard dead objects.
  std::vector<int> ids = objs->getAllIds();

  for (auto x : ids) {
    auto t = objs->getObject(x);
    if (!t->alive())
      objs->removeObject(x);
  }

  // Update the rest.
  ids = objs->getAllIds();

  for (auto x : ids) {
    auto t = objs->getObject(x);
    t->update();
  }
}

enum Engine::Mode Engine::getMode() const {
  return d->mode;
}

void Engine::setMode(enum Mode m) {
  d->mode = m;
}

const std::string& Engine::levelName() const {
  return d->levelName;
}

void Engine::setLevelName(const std::string& s) {
  d->levelName = s;
}

bool Engine::explode(const Point& start, Point end) {
  // Vertical and horizontal lines only.
  if (start.x != end.x && start.y != end.y)
    return false;

  int xInc, yInc;

  if (start.x == end.x && start.y <= end.y) { // Down
    xInc = 0;
    yInc = 1;
    end.y++; // Include end to the range.
  } else if (start.x == end.x && start.y > end.y) { // Up
    xInc = 0;
    yInc = -1;
    end.y--; // Include end to the range.
  } else if (start.x <= end.x && start.y == end.y) { // Right
    xInc = 1;
    yInc = 0;
    end.x++; // Include end to the range.
  } else { // Left
    xInc = -1;
    yInc = 0;
    end.x--; // Include end to the range.
  }

  SPtr<Level> level = d->core.getLevel();
  SPtr<ObjectContainer> objs = d->core.getObjects();

  for (Point t = start; t != end; t.x += xInc, t.y += yInc) {
    // Destroy map cells.
    if (!level->destroy(t)) // Obstacle found.
      break;

    // Destroy dynamic objects.
    std::vector<int> dynamic = objs->getIdsAt(t);

    for (auto x : dynamic) {
      auto obj = objs->getObject(x);
      obj->kill();
    }

    // TODO: Place random bonus.
  }

  return true;
}

void Engine::Private::setupSingle() {
  SPtr<ObjectContainer> objects = core.getObjects();
  SPtr<Level> level = core.getLevel();

  // Create Player character.
  SPtr<ActorMage> player1(new ActorMage(core, GameObject::ActorPlayer1));

  // Assign input.
  SPtr<InputMethod> kbdIn = core.newKbdInput();
  kbdIn->assign(player1->getId());
  player1->setInputMethod(kbdIn);

  // Add to objects container and spawn.
  Point pos = level->nextSpawn();
  player1->move(pos);

  objects->addObject(player1);
  
  // TODO: Add NPCs.
}

void Engine::Private::setupHotseat() {

}

void Engine::Private::setupMulti() {

}
