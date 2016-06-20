#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "commons.hpp"

class Game;

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

  GameObject(Game& core, int id);

  GameObject(const GameObject&) = delete;
  GameObject& operator =(const GameObject&) = delete;

  virtual ~GameObject();

  virtual int getId() const;

  // Called if another object is moved to the same cell with this.
  virtual void onStackWith(int) = 0;

  virtual int print() const = 0;

  virtual Point pos() const;
  virtual bool move(const Point&);

  virtual bool alive() const = 0;
  virtual bool kill() = 0;

  virtual void update() = 0;
protected:
  Game& core;

  int id;
  Point position;
};

#endif
