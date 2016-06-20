/**
 * \file Bomb.hpp
 */
#ifndef BOMB_HPP
#define BOMB_HPP

#include "commons.hpp"
#include "GameObject.hpp"

class Game;
/*!
 * \class Bomb
 * \brief Bomb's description
 * Keeps all information about bomb
 */
class Bomb : public GameObject {
public:
  /*!
   * Base constructor for bombs' registration
   * @param[in]  core Reference to the game core.
   * @param[in]  id  Bomb's identification number
   * \public \memberof Bomb
   */
  Bomb(Game& core, int id);
  /*!
   * Prohibit copying objects
   */
  Bomb(const Bomb&) = delete;
  Bomb& operator =(const Bomb&) = delete;
  /*!
   * Destructor
   * \brief Destructor
   * \public \memberof Bomb
   */
  ~Bomb();
  /*!
   * \fn int print() const
   * \brief Returns bomb's icon(letter): 'B'
   * \public \memberof Bomb
   */
  int print() const;
  /*!
   * \fn bool alive() const
   * \brief Return bomb's state: alive or not alive
   * \public \memberof Bomb
   */
  bool alive() const;
  /*!
   * \fn bool kill()
   * \brief If bomb is alive, it detonates.
   * \public \memberof Bomb
   */
  bool kill();
  /*!
   * \fn void update()
   * \brief Updates bomb state: if time comes, it detonates.
   * \public \memberof Bomb
   */
  void update();
  void onStackWith(int);
  /*!
   * \fn size_t getRadius() const
   * \brief Returns bomb's damage radius
   * \public \memberof Bomb
   */
  size_t getRadius() const;
  /*!
   * \fn void setRadius(size_t r)
   * \brief Sets bomb's damage radius
   * \public \memberof Bomb
   * @param[in] r Damage radius
   */
  void setRadius(size_t);
private:
  class Private;
  UPtr<Private> d;
};

#endif
