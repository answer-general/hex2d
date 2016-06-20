#include "AIInput.hpp"
#include "ActorMage.hpp"
#include "Game.hpp"
#include "ObjectContainer.hpp"
#include "Level.hpp"
#include <array>
#include <vector>

int Abs(int);
int dist2(const Point& a, const Point& b);

class AIInput::Private {
public:
  static const int defaultRadius = 2;

  struct Plan {
    InputMethod::Command best;
    InputMethod::Command good;
    InputMethod::Command bad;
    InputMethod::Command worst;
  };

  Private(Game& c, AIInput& s) : core(c), self(s),
      lastCommand(InputMethod::NoCommand),
      radius(defaultRadius) {};
  Point currentPosition();
  Point findNearestTarget();
  Plan getPlan(const Point& a, const Point& b);
  bool canMove(Point pos, InputMethod::Command dir);

  Game& core;
  AIInput& self;

  InputMethod::Command lastCommand;
  int radius;
};

int Abs(int a) {
  return (a >= 0) ? a : -1 * a;
}

int dist2(const Point& a, const Point& b) {
  int x2 = (a.x - b.x) * (a.x - b.x);
  int y2 = (a.y - b.y) * (a.y - b.y);

  return x2 + y2;
}

AIInput::AIInput(Game& c) : InputMethod(), d(new Private(c, *this)) {}

AIInput::~AIInput() {}

enum InputMethod::Command AIInput::getNextCommand() {
  auto cmd = d->lastCommand;
  d->lastCommand = InputMethod::NoCommand;
  return cmd;
}

void AIInput::update() {
  Point curr = d->currentPosition();
  Point tgt = d->findNearestTarget();

  // Already at goal.
  if (tgt.x == curr.x && tgt.y == curr.y) {
    d->lastCommand = InputMethod::NoCommand;
    return;
  }

  Private::Plan plan = d->getPlan(curr, tgt);
  if (d->canMove(curr, plan.best)) {
    d->lastCommand = plan.best;
  } else if (d->canMove(curr, plan.good)) {
    d->lastCommand = plan.good;
  } else if (d->canMove(curr, plan.bad)) {
    d->lastCommand = plan.bad;
  } else if (d->canMove(curr, plan.worst)) {
    d->lastCommand = plan.worst;
  }
}

int AIInput::sightRadius() const {
  return d->radius;
}

void AIInput::setSightRadius(int r) {
  if (r < 0)
    return;
  d->radius = r;
}

Point AIInput::Private::currentPosition() {
  SPtr<ObjectContainer> objs = core.getObjects();

  SPtr<Actor> a = std::dynamic_pointer_cast<Actor>(
      objs->getObject(self.target));

  return a->pos();
}

Point AIInput::Private::findNearestTarget() {
  SPtr<ObjectContainer> objs = core.getObjects();

  Point pos = currentPosition();

  // Establish search region.
  Point topLeft = pos;
  topLeft.x -= radius;
  topLeft.y -= radius;

  Point bottomRight = pos;
  bottomRight.x += radius;
  bottomRight.y += radius;

  std::vector<int> potentialTargets = objs->getIdsIn(topLeft, bottomRight);

  int tgtId = GameObject::InvalidObject;
  int minDist = 0;

  for (auto x : potentialTargets) {
    if (!GameObject::idIsActor(x)) // Quick check.
      break;

    auto tmp = objs->getObject(x);

    try { // Is it mage?
      std::dynamic_pointer_cast<ActorMage>(tmp);

      if (tgtId == GameObject::InvalidObject || // First target.
          dist2(pos, tmp->pos() < minDist)) { // .. or better than old one.
        minDist = dist2(pos, tmp->pos());
        tgtId = tmp->getId();
      }
    } catch (const std::bad_cast&) {};
  }

  Point res;

  // Target not found.
  if (tgtId == GameObject::InvalidObject) {
    res = Point(-1, -1);
  } else {
    const auto tmp = objs->getObject(tgtId);
    res = tmp->pos();
  }

  return res;
}

AIInput::Private::Plan AIInput::Private::getPlan(const Point& a, const Point& b) {
  Plan res;

  Point diff;
  diff.x = Abs(a.x - b.x);
  diff.y = Abs(a.y - b.y);

  // Look through all 8 configurations.
  if ((a.x < b.x) && (a.y > b.y)) { // 1st quarter.
    if (diff.x < diff.y) { // Steep eighth.
      res.best = InputMethod::MoveRight;
      res.good = InputMethod::MoveUp;
      res.bad = InputMethod::MoveLeft;
      res.worst = InputMethod::MoveDown;
    } else { // Slanting eighth.
      res.best = InputMethod::MoveUp;
      res.good = InputMethod::MoveRight;
      res.bad = InputMethod::MoveDown;
      res.worst = InputMethod::MoveLeft;
    }
    } else if ((a.x > b.x) && (a.y > b.y)) { // 2nd quarter.
    if (diff.x < diff.y) { // Steep eighth.
      res.best = InputMethod::MoveLeft;
      res.good = InputMethod::MoveUp;
      res.bad = InputMethod::MoveRight;
      res.worst = InputMethod::MoveDown;    
    } else { // Slanting eighth.
      res.best = InputMethod::MoveUp;
      res.good = InputMethod::MoveLeft;
      res.bad = InputMethod::MoveDown;
      res.worst = InputMethod::MoveRight;
    }  
  } else if ((a.x > b.x) && (a.y < b.y)) { // 3rd quarter.
    if (diff.x < diff.y) { // Steep eighth.
      res.best = InputMethod::MoveLeft;
      res.good = InputMethod::MoveDown;
      res.bad = InputMethod::MoveRight;
      res.worst = InputMethod::MoveUp;
    } else { // Slanting eighth.
      res.best = InputMethod::MoveDown;
      res.good = InputMethod::MoveLeft;
      res.bad = InputMethod::MoveUp;
      res.worst = InputMethod::MoveRight;
    }  
  } else { // 4th quarter.
    if (diff.x < diff.y) { // Steep eighth.
      res.best = InputMethod::MoveRight;
      res.good = InputMethod::MoveDown;
      res.bad = InputMethod::MoveLeft;
      res.worst = InputMethod::MoveUp;
    } else { // Slanting eighth.
      res.best = InputMethod::MoveDown;
      res.good = InputMethod::MoveRight;
      res.bad = InputMethod::MoveUp;
      res.worst = InputMethod::MoveLeft;
    }  
  }

  return res;
}

bool AIInput::Private::canMove(Point p, enum Command dir) {
  const auto level = core.getLevel();

  switch (dir) {
  case InputMethod::MoveUp:
    --p.y;
    break;
  case InputMethod::MoveDown:
    ++p.y;
    break;
  case InputMethod::MoveLeft:
    --p.x;
    break;
  case InputMethod::MoveRight:
    ++p.x;
    break;
  default: // Not a move command.
    return false;
    break;
  };

  if (level->canCross(p))
    return true;
  else
    return false;
}
