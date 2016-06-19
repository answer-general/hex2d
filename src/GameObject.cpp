#include "GameObject.hpp"


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

GameObject::GameObject(int id) : id(id) {}

GameObject::~GameObject() {}

int GameObject::getId() const {
  return id;
}

