#include "Bonus.hpp"
#include "GameObject.hpp"
#include "ObjectContainer.hpp"
#include "Actor.hpp"
#include "Game.hpp"

Bonus::Bonus(Game& c, int id, int ticks) : GameObject(id),
    core(c), ticks(ticks), position(-1, -1) {}

Bonus::~Bonus() {}

Point Bonus::pos() const { return position; }

bool Bonus::move(const Point& pos) {
  position = pos;
  return true;
}

bool Bonus::alive() const {
  if (this->pickedBy() == GameObject::InvalidObject)
    return true;
  else
    return false;
}

bool Bonus::kill() { return false; }
 
void Bonus::update() {}

SpeedBonus::SpeedBonus(Game& c, int id, int ticks)
    : Bonus(c, id, ticks), picker(GameObject::InvalidObject) {}

SpeedBonus::~SpeedBonus() {}

int SpeedBonus::pickedBy() const {
  return picker;
}

bool SpeedBonus::pickUp(int id) {
  if (!GameObject::idIsActor(id))
    return false;
  SPtr<GameObject> obj = core.getObjects()->getObject(id);
  SPtr<Actor> act = std::dynamic_pointer_cast<Actor>(obj);
  act->boostSpeed(defaultSpeed, ticks);
  return true;
}

int SpeedBonus::print() const {
  return 'S';
}

InvulBonus::InvulBonus(Game& c, int id, int ticks)
    : Bonus(c, id, ticks), picker(GameObject::InvalidObject) {}

InvulBonus::~InvulBonus() {}

int InvulBonus::pickedBy() const {
  return picker;
}

bool InvulBonus::pickUp(int id) {
  if (!GameObject::idIsActor(id))
    return false;
  SPtr<GameObject> obj = core.getObjects()->getObject(id);
  SPtr<Actor> act = std::dynamic_pointer_cast<Actor>(obj);
  act->boostInvul(ticks);
  return true;
}

int InvulBonus::print() const {
  return 'I';
}

BombCountBonus::BombCountBonus(Game& c, int id, int ticks)
    : Bonus(c, id, ticks), picker(GameObject::InvalidObject) {}

BombCountBonus::~BombCountBonus() {}

int BombCountBonus::pickedBy() const {
  return picker;
}

bool BombCountBonus::pickUp(int id) {
  if (!GameObject::idIsActor(id))
    return false;
  SPtr<GameObject> obj = core.getObjects()->getObject(id);
  SPtr<Actor> act = std::dynamic_pointer_cast<Actor>(obj);
  act->boostBombCount(defaultCount, ticks);
  return true;
}

int BombCountBonus::print() const {
  return 'C';
}

BombRangeBonus::BombRangeBonus(Game& c, int id, int ticks)
    : Bonus(c, id, ticks), picker(GameObject::InvalidObject) {}

BombRangeBonus::~BombRangeBonus() {}

int BombRangeBonus::pickedBy() const {
  return picker;
}

bool BombRangeBonus::pickUp(int id) {
  if (!GameObject::idIsActor(id))
    return false;
  SPtr<GameObject> obj = core.getObjects()->getObject(id);
  SPtr<Actor> act = std::dynamic_pointer_cast<Actor>(obj);
  act->boostBombRadius(defaultRange, ticks);
  return true;
}

int BombRangeBonus::print() const {
  return 'R';
}
