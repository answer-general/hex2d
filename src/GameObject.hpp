#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "commons.hpp"

class GameObject {
public:
  // Defines ids for static objects and id ranges for dynamic ones.
  // Typical size for dynamic sections -- 128.
  enum ObjectId {
    InvalidObject = -1,
    // Actors section. Mixed.
    ActorMinId = 0,
    ActorPlayer1,
    ActorPlayer2,
    ActorMaxId = 127,
    // Bombs section
    BombMinId = 128,
    BombMaxId = 255,
    // Bonus section.
    // Subdivide for bonus types?
    BonusMinId = 256,
    BonusMaxId = 383
  };

  static bool idIsActor(int id);
  static bool idIsBomb(int id);
  static bool idIsBonus(int id);

  static int genActorId();
  static int genBombId();
  static int genBonusId();

  GameObject(int id);

  GameObject(const GameObject&) = delete;
  GameObject& operator =(const GameObject&) = delete;

  virtual ~GameObject();

  virtual int getId() const;

  virtual int print() const = 0;

  virtual Point pos() const = 0;
  virtual bool move(const Point&) = 0;

  virtual bool alive() const = 0;
  virtual bool kill() = 0;
 
  virtual void update() = 0;
protected:
  int id;
};

#endif
