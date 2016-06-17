#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

enum class ObjectId {
  InvalidObject = -1,

  Player1 = 0,
  Player2,
  Player3,
  Player4,
  Player5,
  Player6,
  MaxPlayers,

  WoodTile,
  StoneTile,
  FloorTile,
};


class GameObject {
public:
  GameObject(int id) : id(id) {};

  GameObject(const GameObject&) = delete;
  GameObject& operator =(const GameObject&) = delete;

  virtual ~GameObject() {};

  virtual int getId() const { return id; };

  virtual bool explodable() const = 0;
  virtual bool passable() const = 0;
protected:
  int id;
};

#endif
