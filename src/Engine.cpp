#include "ActorMage.hpp"
#include "Engine.hpp"
#include "Game.hpp"
#include "ObjectContainer.hpp"
#include "GameObject.hpp"
#include "Level.hpp"

class Engine::Private {
public:
  Private(Game& c) : core(c), running(false),
      //Set default simulation parameters.
      mode(Engine::ModeSingle) {};

  void setupSingle();

  Game& core;
  bool running;
  enum Engine::Mode mode;
};

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
  objects->addObject(player1);
  level->spawn(player1->getId());
  
  // TODO: Add NPCs.
  // do {
  //
  //} while (level->spawn());
}

Engine::Engine(Game& core) : d(new Private(core)) {}

Engine::~Engine() {}

bool Engine::isRunning() const {
  return d->running;
}

void Engine::run() {
  if (!d->running) {
    if (d->mode == ModeSingle)
      d->setupSingle();
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
  d->core.getObjects()->updateAll();
}

enum Engine::Mode Engine::getMode() const {
  return d->mode;
}

void Engine::setMode(enum Mode m) {
  d->mode = m;
}

bool Engine::explode(const Point& start, const Point& end) {
  if (start.x != end.x || start.y != end.y)
    return false;

  SPtr<Level> level = d->core.getLevel();
  SPtr<ObjectContainer> objs = d->core.getObjects();

  if (start.x == end.x) { // Vertical.
    Point low = (start.y < end.y)? start : end;
    Point high = (start.y < end.y)? end : start;

    for (low.y = low.y; low.y <= high.y; ++low.y) {
      Cell c = level->getCellAt(low);

      int tid;
      c.back(tid);
      auto tobj = objs->getObject(tid);

      // Obstacle encoutered, stop.
      if (!tobj->explodable() && !tobj->passable())
        break;

      // Remove all explodable tiles.
      Cell tmp;
      while (c.size() != 0) {
        c.back(tid);
        c.pop();

        tobj = objs->getObject(tid);
        
        if (!tobj->explodable())
          tmp.push(tid);
        else
          objs->removeObject(tid);
      }

      // Now set order back to normal.
      c.clear();
      while (tmp.size() != 0) {
        int t;
        tmp.back(t);
        tmp.pop();
        c.push(t);
      }
    }
  } else { // Horizontal.
    Point low = (start.x < end.x)? start : end;
    Point high = (start.x < end.x)? end : start;

    for (low.x = low.x; low.x <= high.x; ++low.x) {
      Cell c = level->getCellAt(low);

      int tid;
      c.back(tid);
      auto tobj = objs->getObject(tid);

      // Obstacle encoutered, stop.
      if (!tobj->explodable() && !tobj->passable())
        break;

      // Remove all explodable tiles.
      Cell tmp;
      while (c.size() != 0) {
        c.back(tid);
        c.pop();

        tobj = objs->getObject(tid);
        
        if (!tobj->explodable())
          tmp.push(tid);
        else
          objs->removeObject(tid);
      }

      // Now set order back to normal.
      c.clear();
      while (tmp.size() != 0) {
        int t;
        tmp.back(t);
        tmp.pop();
        c.push(t);
      }    
    }
  }

  return true;
}
