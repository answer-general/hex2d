#include "Bonus.hpp"
#include "GameObject.hpp"
#include "ObjectContainer.hpp"
#include "Actor.hpp"
#include "Game.hpp"

Bonus::Bonus(Game& c, int id, int ticks) : GameObject(c, id),
    ticks(ticks) {}

Bonus::~Bonus() {}

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

void SpeedBonus::onStackWith(int id) {
  if (!GameObject::idIsActor(id))
    return;
  SPtr<GameObject> obj = core.getObjects()->getObject(id);
  SPtr<Actor> act = std::dynamic_pointer_cast<Actor>(obj);
  act->boostSpeed(defaultSpeed, ticks);

  picker = id;
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

void InvulBonus::onStackWith(int id) {
  if (!GameObject::idIsActor(id))
    return;
  SPtr<GameObject> obj = core.getObjects()->getObject(id);
  SPtr<Actor> act = std::dynamic_pointer_cast<Actor>(obj);
  act->boostInvul(ticks);

  picker = id;
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

void BombCountBonus::onStackWith(int id) {
  if (!GameObject::idIsActor(id))
    return;
  SPtr<GameObject> obj = core.getObjects()->getObject(id);
  SPtr<Actor> act = std::dynamic_pointer_cast<Actor>(obj);
  act->boostBombCount(defaultCount, ticks);

  picker = id;
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

void BombRangeBonus::onStackWith(int id) {
  if (!GameObject::idIsActor(id))
    return;
  SPtr<GameObject> obj = core.getObjects()->getObject(id);
  SPtr<Actor> act = std::dynamic_pointer_cast<Actor>(obj);
  act->boostBombRadius(defaultRange, ticks);

  picker = id;
}

int BombRangeBonus::print() const {
  return 'R';
}
