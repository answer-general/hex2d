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

  Private(Game& c, AIInput& s) : core(c), self(s),
      lastCommand(InputMethod::NoCommand),
      radius(defaultRadius) {};
  Point currentPosition();
  Point findNearestTarget();
  bool canMove(Point pos, enum InputMethod::Command direction);

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

  Point diff;
  diff.x = Abs(tgt.x - curr.x);
  diff.y = Abs(tgt.y - curr.y);

  Point inc(0,0);
  if ((tgt.x - curr.x) > 0)
    inc.x = 1;
  else if ((tgt.x - curr.x) < 0)
    inc.x = -1;

  if ((tgt.y - curr.y) > 0)
    inc.y = 1;
  else if ((tgt.y - curr.y) < 0)
    inc.y = -1;

  // Try optimal direction.
//  if (diff.x < diff.y)
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

bool AIInput::Private::canMove(Point p, enum InputMethod::Command dir) {
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
