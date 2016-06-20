/**
 * \file ActorMage.hpp
 */
#ifndef ACTOR_MAGE_HPP
#define ACTOR_MAGE_HPP

#include "commons.hpp"
#include "Actor.hpp"
/*!
 * \class ActorMage
 * \brief - class for player characters
 *  Class for all player characters
 */
class ActorMage : public Actor {
public:
  /*!
   * Base constructor for characters' registration
   * @param[in]  core Reference to the game core.
   * @param[in]  id  Character's identification number
   * \public \memberof ActorMage
   */
  ActorMage(Game&, int);
  /*!
   * Prohibit copying objects
   */
  ActorMage(const ActorMage&) = delete;
  ActorMage& operator =(const ActorMage&) = delete;
  /*!
   * Destructor
   * \public \memberof ActorMage
   */
  ~ActorMage();
  /*!
   * \fn int print() const
   * \brief Returns player's character icon(letter): '$'
   * \public \memberof ActorMage
   */
  int print() const;
  /*!
   * \fn bool alive() const
   * \brief Return player's character state: alive or not alive
   * \public \memberof ActorMage
   */
  bool alive() const;
  /*!
   * \fn bool kill()
   * \brief Kills player's character
   * \public \memberof ActorMage
   * 
   */
  bool kill();
  /*!
   * \fn void update()
   * \brief Updates player's character position
   * \public \memberof ActorMage
   */
  void update();
  /*!
   * \fn void onStackWith(int)
   * \brief Attack enemies
   * \public \memberof ActorMage
   * @param[in] id Enemies identification number
   */
  void onStackWith(int);

  /// Bonus effects -- provide temporary boosts.
  /*!
   * \fn void boostBombCount(int newCount, int durationTicks)
   * \brief Increase the number of bombs
   * \public \memberof ActorMage
   * @param[in] newCount New number of bombs
   * @param[in] durationTicks Boost's duration
   */
  void boostBombCount(int newCount, int durationTicks);
  /*!
   * \fn void boostBombRadius(int newVal, int durationTicks);
   * \brief Boosts bomb's radius
   * \public \memberof ActorMage
   * @param[in] newVal New bomb's radius
   * @param[in] durationTicks Boost's duration
   */
  void boostBombRadius(int newVal, int durationTicks);
  /*!
   * \fn void boostInvul(int durationTicks)
   * \brief Makes the character invulnerable to bombs 
   * \public \memberof ActorMage
   * @param[in] durationTicks Boost's duration
   */
  void boostInvul(int durationTicks);
  /*!
   * \fn void boostSpeed(int newVal, int durationTicks)
   * \brief Accelerate bombs' speed 
   * \public \memberof ActorMage
   * @param[in] newVal New speed's value
   * @param[in] durationTicks Boost's duration
   */
  void boostSpeed(int newVal, int durationTicks);
private:
  class Private;
  UPtr<Private> d;
};

#endif
