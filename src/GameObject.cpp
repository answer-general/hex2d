#include "GameObject.hpp"
#include "Game.hpp"
#include "Level.hpp"
#include "ObjectContainer.hpp"

bool GameObject::idIsActor(int id) {
  return (id > ActorMinId) && (id < ActorMaxId);
}

bool GameObject::idIsBomb(int id) {
  return (id > BombMinId) && (id < BombMaxId);
}

bool GameObject::idIsBonus(int id) {
  return (id > BonusMinId) && (id < BonusMaxId);
}

int GameObject::genActorId() {
  static int aid = ActorMinId + 1;
  if (aid == ActorMaxId)
    aid = ActorMinId + 1;
  return aid++;
}

int GameObject::genBombId() {
    static int bid = BombMinId + 1;
    if (bid == BombMaxId)
      bid = BombMinId + 1;
    return bid++;
}

int GameObject::genBonusId() {
  static int bonid = BonusMinId + 1;
  if (bonid == BonusMaxId)
    bonid = BonusMinId + 1;
  return bonid++;
}

GameObject::GameObject(Game& c, int id) : core(c), id(id), position(-1, -1) {}

GameObject::~GameObject() {}

int GameObject::getId() const {
  return id;
}

Point GameObject::pos() const {
  return position;
}

bool GameObject::move(const Point& tgt) {
  SPtr<Level> l = core.getLevel();

  if (alive() && l->canCross(tgt)) {
    SPtr<ObjectContainer> objects = core.getObjects();

    std::vector<int> stack = objects->getIdsIn(tgt, tgt);
    for (auto x : stack) {
      auto o = objects->getObject(x);
      o->onStackWith(id);
      onStackWith(o->getId());
    }

    position = tgt;
  } else {
    return false;
  }

  return true;
}

