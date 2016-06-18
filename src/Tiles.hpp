#ifndef TILES_HPP
#define TILES_HPP

#include "GameObject.hpp"

class WoodTile : public GameObject {
public:
  WoodTile() : GameObject(GameObject::TileWood) {};
  ~WoodTile() {};

  bool explodable() const { return true; };
  bool passable() const { return false; };
};

class StoneTile : public GameObject {
public:
  StoneTile() : GameObject(GameObject::TileStone) {};
  ~StoneTile() {};

  bool explodable() const { return false; };
  bool passable() const { return false; };
};

class FloorTile : public GameObject {
public:
  FloorTile() : GameObject(GameObject::TileFloor) {};
  ~FloorTile() {};

  bool explodable() const { return false; };
  bool passable() const { return true; };
};

#endif
