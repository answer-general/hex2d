/**
 * \file Bonus.hpp
 */
#ifndef BONUS_HPP
#define BONUS_HPP

#include "commons.hpp"
#include "GameObject.hpp"

class Game;
/*!
 * \class Bonus
 * \brief Base class for all bonuses
 * Base class for all bonuses, keeps main information about bonuses
 */
class Bonus : public GameObject {
public:
  /*!
   * \enum BonusType
   * Type of Bonus
   * \public \memberof Bonus
   */
  enum BonusType {
    BonusSpeed, /*!< Accelerate bombs' speed */
    BonusInvul, /*!< Invulnerable to bombs */
    BonusCount, /*!< Increase the number of bombs */
    BonusRange,
    BonusTypes
  };
  /*!
   * \var static const int defaultTicks = 200
   * Default time, while bonus is active
   * \public \memberof Bonus
   */
  static const int defaultTicks = 200;
  /*!
   * Base constructor for bonus registration
   * @param[in]  core Reference to the game core.
   * @param[in]  id  Bonus's identification number
   * @param[in]  ticks  Default time, while bonus is active
   * \public \memberof Bonus
   */
  Bonus(Game& core, int id, int ticks = defaultTicks);
  /*!
   * Prohibit copying objects
   */
  Bonus(const Bonus&) = delete;
  Bonus& operator =(const Bonus&) = delete;
  /*!
   * Destructor
   * Delete bonus
   * \pure \public \memberof Bonus
   */
  virtual ~Bonus();
  /*!
   * \fn bool alive() const
   * If bonus is still available or have been already picked by player.
   * \public \memberof Bonus
   */
  bool alive() const;
  
  bool kill();
  void update();

  /// /return GameObject::InvalidObject, if not picked.
  /*!
   * \var virtual int pickedBy() const = 0
   * Picked or not picked by player
   * \pure \public \memberof Bonus
   */
  virtual int pickedBy() const = 0;
  
protected:
  int ticks;
  Point position;
};

/*!
 * \class SpeedBonus
 * \brief Subclass of Bonus
 * Subclass for speed bonuses, keeps information about bonuses
 */
class SpeedBonus : public Bonus {
public:
  /*!
   * Constructor for speed bonus registration
   * @param[in]  core Reference to the game core.
   * @param[in]  id  Bonus's identification number
   * @param[in]  ticks  Default time, while bonus is active
   * \public \memberof SpeedBonus
   */
  SpeedBonus(Game& core, int id, int ticks = Bonus::defaultTicks);
  /*!
   * Prohibit copying objects
   */
  SpeedBonus(const SpeedBonus&) = delete;
  SpeedBonus& operator =(const SpeedBonus&) = delete;
  
  ~SpeedBonus();
  /*!
   * \var int pickedBy() const
   * Picked or not picked by player
   * \public \memberof SpeedBonus
   */
  int pickedBy() const;
  /*!
   * \fn void onStackWith(int)
   * If player found bonus, he picked it up.
   * \public \memberof SpeedBonus
   */
  void onStackWith(int);
  /*!
   * \fn int print() const
   * \brief Returns bomb's icon(letter)
   * \public \memberof SpeedBomb
   */
  int print() const;
private:
  static const int defaultSpeed = 2;
  int picker;
};
/*!
 * \class InvulBonus
 * \brief Subclass of Bonus
 * Subclass for invulnerable bonuses, keeps information about bonuses
 */
class InvulBonus : public Bonus {
public:
  /*!
   * Constructor for bonus registration
   * @param[in]  core Reference to the game core.
   * @param[in]  id  Bonus's identification number
   * @param[in]  ticks  Default time, while bonus is active
   * \public \memberof InvulBonus
   */
  InvulBonus(Game& core, int id, int ticks = Bonus::defaultTicks);
  /*!
   * Prohibit copying objects
   */
  InvulBonus(const InvulBonus&) = delete;
  InvulBonus& operator =(const InvulBonus&) = delete;

  ~InvulBonus();
  /*!
   * \var int pickedBy() const
   * Picked or not picked by player
   * \public \memberof InvulBonus
   */
  int pickedBy() const;
  /*!
   * \fn void onStackWith(int)
   * If player found bonus, he picked it up.
   * \public \memberof InvulBonus
   */
  void onStackWith(int);
  
  /*!
   * \fn int print() const
   * \brief Returns bomb's icon(letter)
   * \public \memberof InvulBomb
   */
  int print() const;
private:
  int picker;
};

class BombCountBonus : public Bonus {
public:
  /*!
   * Constructor for bonus registration
   * @param[in]  core Reference to the game core.
   * @param[in]  id  Bonus's identification number
   * @param[in]  ticks  Default time, while bonus is active
   * \public \memberof BombCountBonus
   */
  BombCountBonus(Game& core, int id, int ticks = Bonus::defaultTicks);
  /*!
   * Prohibit copying objects
   */
  BombCountBonus(const BombCountBonus&) = delete;
  BombCountBonus& operator =(const BombCountBonus&) = delete;

  ~BombCountBonus();
  /*!
   * \var int pickedBy() const
   * Picked or not picked by player
   * \public \memberof BombCountBonus
   */
  int pickedBy() const;
  /*!
   * \fn void onStackWith(int)
   * If player found bonus, he picked it up.
   * \public \memberof BombCountBonus
   */
  void onStackWith(int);
  /*!
   * \fn int print() const
   * \brief Returns bomb's icon(letter)
   * \public \memberof BombCountBonus
   */
  int print() const;
private:
  static const int defaultCount = 4;
  int picker;
};

class BombRangeBonus : public Bonus {
public:
  /*!
   * Constructor for bonus registration
   * @param[in]  core Reference to the game core.
   * @param[in]  id  Bonus's identification number
   * @param[in]  ticks  Default time, while bonus is active
   * \public \memberof BombRangeBonus
   */
  BombRangeBonus(Game& core, int id, int ticks = Bonus::defaultTicks);
  /*!
   * Prohibit copying objects
   */
  BombRangeBonus(const BombRangeBonus&) = delete;
  BombRangeBonus& operator =(const BombRangeBonus&) = delete;

  ~BombRangeBonus();
  /*!
   * \var int pickedBy() const
   * Picked or not picked by player
   * \public \memberof BombRangeBonus
   */
  int pickedBy() const;
  /*!
   * \fn void onStackWith(int)
   * If player found bonus, he picked it up.
   * \public \memberof BombRangeBonus
   */
  void onStackWith(int);

  /*!
   * \fn int print() const
   * \brief Returns bomb's icon(letter)
   * \public \memberof BombRangeBonus
   */
  int print() const;
private:
  static const int defaultRange = 4;
  int picker;
};

#endif
