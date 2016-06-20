/*!
 * \file GameObject.hpp
 */
#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "commons.hpp"

class Game;
/*!
 * \class GameObject
 * Basic class that defines game objects.
 */
class GameObject {
public:
  /*!
   * \enum ObjectId
   * Defines ids for static objects and id ranges for dynamic ones.
   * Typical size for dynamic sections -- 128.
   * \public \memberof GameObject
   */
  enum ObjectId {
    InvalidObject = -1, /*!< InvalidObject = -1 */
    /// Actors section. Mixed.
    ActorMinId = 0, /*!< ActorMinId = 0 */
    ActorPlayer1, /*!< ActorPlayer1 */
    ActorPlayer2,  /*!< ActorPlayer2 */
    ActorMaxId = 127, /*!< ActorMaxId = 127 */
    /// Bombs section
    BombMinId = 128, /*!< BombMinId = 128 */
    BombMaxId = 255, /*!< BombMaxId = 255 */
    /// Bonus section.
    // Subdivide for bonus types?
    BonusMinId = 256, /*!< BonusMinId = 256 */
    BonusMaxId = 383 /*!< BonusMaxId = 383 */
  };

  /*!
   * \fn static bool idIsActor(int id)
   * Check, if object with identification number = id is an actor.
   * @param[in] id Object's identification number.
   * \public \memberof GameObject
   */
  static bool idIsActor(int id);
  /*!
   * \fn static bool idIsBomb(int id)
   * Check, if object with identification number = id is a bomb.
   * @param[in] id Object's identification number.
   * \public \memberof GameObject
   */
  static bool idIsBomb(int id);
  /*!
   * \fn static bool idIsBonus(int id)
   * Check, if object with identification number = id is a bonus.
   * @param[in] id Object's identification number.
   * \public \memberof GameObject
   */
  static bool idIsBonus(int id);

  /*!
   * \fn static int genActorId()
   * Generate a new identification number for a new actor.
   * @param[in] id Object's identification number.
   * \public \memberof GameObject
   */
  static int genActorId();
  /*!
   * \fn static int genBombId()
   * Generate a new identification number for a new bomb.
   * @param[in] id Object's identification number.
   * \public \memberof GameObject
   */
  static int genBombId();
  /*!
   * \fn static int genBonusId()
   * Generate a new identification number for a new bonus.
   * @param[in] id Object's identification number.
   * \public \memberof GameObject
   */
  static int genBonusId();

  /*!
   * Base constructor.
   * @param[in]  core Reference to the game core.
   * @param[in]  id  Character's identification number
   * \public \memberof GameObject
   */
  GameObject(Game& core, int id);
  /*!
   * Prohibit copying objects
   */
  GameObject(const GameObject&) = delete;
  GameObject& operator =(const GameObject&) = delete;

  /*!
   * Virtual destructor.
   * \pure \public \memberof GameObject
   */
  virtual ~GameObject();
  /*!
   * \fn virtual int getId() const
   * Get object's identification number.
   * \pure \public \memberof GameObject
   */
  virtual int getId() const;

  /*!
   * \fn virtual void onStackWith(int) = 0
   * Called if another object is moved to the same cell with this.
   * \pure \public \memberof GameObject
   */
  virtual void onStackWith(int) = 0;
  /*!
   * \fn virtual int print() const = 0
   * Print object's parametres.
   * \pure \public \memberof GameObject
   */
  virtual int print() const = 0;

  /*!
   * \fn virtual Point pos() const
   * Return object's position
   * \pure \public \memberof GameObject
   */
  virtual Point pos() const;
  /*!
   * \fn virtual bool move(const Point&)
   * Object moves.
   * \pure \public \memberof GameObject
   */
  virtual bool move(const Point&);
  
  /*!
   * \fn virtual bool alive() const = 0
   * Check if an object is still alive/available.
   * \pure \public \memberof GameObject
   */
  virtual bool alive() const = 0;
  /*!
   * \fn virtual bool kill() = 0
   * Kills an object.
   * \pure \public \memberof GameObject
   */
  virtual bool kill() = 0;
  /*!
   * \fn virtual void update() = 0
   * Updates object's state.
   * \pure \public \memberof GameObject
   */
  virtual void update() = 0;
protected:
  Game& core;
  int id;
  Point position;
};

#endif
