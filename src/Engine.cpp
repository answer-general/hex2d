#include <stdlib.h>
#include <string>
#include <vector>
#include "ActorMage.hpp"
#include "ActorImp.hpp"
#include "Bonus.hpp"
#include "Engine.hpp"
#include "Game.hpp"
#include "ObjectContainer.hpp"
#include "GameObject.hpp"
#include "Level.hpp"

class Engine::Private {
public:
  static const enum Engine::Mode defaultMode;
  static const int bonusChance;

  Private(Game& c) : core(c), running(false),
      mode(defaultMode), levelName() {};

  void setupSingle();
  void setupHotseat();
  void setupMulti();

  void genBonusAt(const Point& start, const Point& end);

  Game& core;

  bool running;
  enum Engine::Mode mode;

  std::string levelName;
};

const enum Engine::Mode Engine::Private::defaultMode = Engine::ModeSingle;
// Each bomb generates 4 explosions -> 8%
const int Engine::Private::bonusChance = 100;//2;

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
    if (!t->alive()) {
      if (t->getId() == d->core.getPCId()) // Oops... Player died.
        d->core.setPC(GameObject::InvalidObject);
      objs->removeObject(x);
    }
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

bool Engine::explode(Point start, Point end) {
  // Vertical and horizontal lines only.
  if (start.x != end.x && start.y != end.y)
    return false;

  int xInc, yInc;

  if (start.x == end.x && start.y <= end.y) { // Down
    xInc = 0;
    yInc = 1;
  } else if (start.x == end.x && start.y > end.y) { // Up
    xInc = 0;
    yInc = -1;
  } else if (start.x <= end.x && start.y == end.y) { // Right
    xInc = 1;
    yInc = 0;
  } else { // Left
    xInc = -1;
    yInc = 0;
  }

  SPtr<Level> level = d->core.getLevel();
  SPtr<ObjectContainer> objs = d->core.getObjects();

  Point t;
  for (t = start; t != end; t.x += xInc, t.y += yInc) {
    if (!level->destroy(t))
      break;
  }
  // Include end.
  if (t == end) {
    if (!level->destroy(t)) {
      t.x -= xInc;
      t.y -= yInc;
    }
  }

  std::vector<int> dynamic;
  if (start < end)
    dynamic = objs->getIdsIn(start, t);
  else
    dynamic = objs->getIdsIn(t, start);

  for (auto x : dynamic) {
    auto obj = objs->getObject(x);
    obj->kill();
  }


  // Generate random bonus.
  if ((rand() % 100) <= d->bonusChance) {
    if (start < end)
      d->genBonusAt(start, t);
    else
      d->genBonusAt(t, start);
  }

  return true;
}

void Engine::Private::setupSingle() {
  SPtr<ObjectContainer> objects = core.getObjects();
  SPtr<Level> level = core.getLevel();

  // Create Player character.
  SPtr<ActorMage> player1(new ActorMage(core, GameObject::genActorId()));

  // Assign input.
  SPtr<InputMethod> kbdIn = core.newKbdInput();
  kbdIn->assign(player1->getId());
  player1->setInputMethod(kbdIn);

  // Add to objects container and spawn.
  Point pos = level->nextSpawn();
  player1->move(pos);

  objects->addObject(player1);
  core.setPC(player1->getId());

  Point badPos(-1,-1);
  for (Point p = level->nextSpawn(); p != badPos; p = level->nextSpawn()) {
    SPtr<ActorImp> npc(new ActorImp(core, GameObject::genActorId()));
    npc->move(p);

    // TODO: Connect AI input.

    objects->addObject(npc);
  }
}

void Engine::Private::setupHotseat() {

}

void Engine::Private::setupMulti() {

}

void Engine::Private::genBonusAt(const Point& start, const Point& end) {
  // Select random location.
  Point pos;
  if (start.y == end.y) { // Horizontal.
    pos.y = start.y;
    pos.x = (rand() % (end.x - start.x)) + start.x;
  } else { // Vertical.
    pos.x = start.x;
    pos.y = (rand() % (end.y - start.y)) + start.y;
  }

  // Create random bonus.
  SPtr<Bonus> b;

  int type = rand() % Bonus::BonusTypes;
  switch (type) {
  case Bonus::BonusSpeed:
    b.reset(new SpeedBonus(core, GameObject::genBonusId()));
    break;
  case Bonus::BonusInvul:
    b.reset(new InvulBonus(core, GameObject::genBonusId()));
    break;
  case Bonus::BonusCount:
    b.reset(new BombCountBonus(core, GameObject::genBonusId()));
    break;
  case Bonus::BonusRange:
    b.reset(new BombRangeBonus(core, GameObject::genBonusId()));
    break;
  default:
    return;
    break;
  };
  b->move(pos);

  // Add bonus to the map.
  core.getObjects()->addObject(b);
}
