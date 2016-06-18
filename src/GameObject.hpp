#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

class GameObject {
public:
  // Defines ids for static objects and id ranges for dynamic ones.
  // Typical size for dynamic sections -- 128.
  enum ObjectId {
    InvalidObject = -1,
    // Tile types section. Entirely static.
    TileMinId = 0,
    TileWood,
    TileStone,
    TileFloor,
    TileMaxId,
    // Actors section. Mixed.
    ActorMinId = 127,
    ActorPlayer1,
    ActorPlayer2,
    ActorMaxId = 255,
    // Bombs section
    BombMinId = 256,
    BombMaxId = 383,
    // Bonus section.
    // Subdivide for bonus types?
    BonusMinId = 384,
    BonusMaxId = 511
  };

  static bool idIsActor(int id) { return (id > ActorMinId) && (id < ActorMaxId); };
  static bool idIsBomb(int id) { return (id > BombMinId) && (id < BombMaxId); };
  static bool idIsBonus(int id) { return (id > BonusMinId) && (id < BonusMaxId); };
 
  GameObject(int id) : id(id) {};

  GameObject(const GameObject&) = delete;
  GameObject& operator =(const GameObject&) = delete;

  virtual ~GameObject() {};

  virtual int getId() const { return id; };

  virtual bool explodable() const = 0;
  virtual bool passable() const = 0;

  virtual void update() {};
protected:
  int id;
};

#endif
