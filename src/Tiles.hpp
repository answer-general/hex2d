#ifndef TILES_HPP
#define TILES_HPP

#include "GameObject.hpp"

class WoodTile : public GameObject {
public:
  WoodTile() : GameObject((int)ObjectId::WoodTile) {};
  ~WoodTile() {};

  bool explodable() const { return true; };
  bool passable() const { return false; };
};

class StoneTile : public GameObject {
public:
  StoneTile() : GameObject((int)ObjectId::StoneTile) {};
  ~StoneTile() {};

  bool explodable() const { return false; };
  bool passable() const { return false; };
};

class FloorTile : public GameObject {
public:
  FloorTile() : GameObject((int)ObjectId::FloorTile) {};
  ~FloorTile() {};

  bool explodable() const { return false; };
  bool passable() const { return true; };
};

#endif
