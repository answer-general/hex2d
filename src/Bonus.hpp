#ifndef BONUS_HPP
#define BONUS_HPP

#include "commons.hpp"
#include "GameObject.hpp"

class Game;

class Bonus : public GameObject {
public:
  enum BonusType {
    BonusSpeed,
    BonusInvul,
    BonusCount,
    BonusRange,
    BonusTypes
  };

  static const int defaultTicks = 200;

  Bonus(Game& core, int id, int ticks = defaultTicks);

  Bonus(const Bonus&) = delete;
  Bonus& operator =(const Bonus&) = delete;

  virtual ~Bonus();

  Point pos() const;
  bool move(const Point&);

  bool alive() const;
  bool kill();
 
  void update();

  /// /return GameObject::InvalidObject, if not picked.
  virtual int pickedBy() const = 0;

  /// /return false if already picked.
  virtual bool pickUp(int) = 0;
protected:
  Game& core;
  int ticks;
  Point position;
};

class SpeedBonus : public Bonus {
public:
  SpeedBonus(Game& core, int id, int ticks = Bonus::defaultTicks);

  SpeedBonus(const SpeedBonus&) = delete;
  SpeedBonus& operator =(const SpeedBonus&) = delete;

  ~SpeedBonus();

  int pickedBy() const;
  bool pickUp(int);

  int print() const;
private:
  static const int defaultSpeed = 2;
  int picker;
};

class InvulBonus : public Bonus {
public:
  InvulBonus(Game& core, int id, int ticks = Bonus::defaultTicks);

  InvulBonus(const InvulBonus&) = delete;
  InvulBonus& operator =(const InvulBonus&) = delete;

  ~InvulBonus();

  int pickedBy() const;
  bool pickUp(int);

  int print() const;
private:
  int picker;
};

class BombCountBonus : public Bonus {
public:
  BombCountBonus(Game& core, int id, int ticks = Bonus::defaultTicks);

  BombCountBonus(const BombCountBonus&) = delete;
  BombCountBonus& operator =(const BombCountBonus&) = delete;

  ~BombCountBonus();

  int pickedBy() const;
  bool pickUp(int);

  int print() const;
private:
  static const int defaultCount = 4;
  int picker;
};

class BombRangeBonus : public Bonus {
public:
  BombRangeBonus(Game& core, int id, int ticks = Bonus::defaultTicks);

  BombRangeBonus(const BombRangeBonus&) = delete;
  BombRangeBonus& operator =(const BombRangeBonus&) = delete;

  ~BombRangeBonus();

  int pickedBy() const;
  bool pickUp(int);

  int print() const;
private:
  static const int defaultRange = 4;
  int picker;
};

#endif
