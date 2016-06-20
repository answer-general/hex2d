/**
 * \file Actor.hpp
 */
#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "commons.hpp"
#include "GameObject.hpp"
#include "InputMethod.hpp"

class Game;
/*!
 * \class Actor
 * \brief - base class for all game characters
 *  Base class for all game characters, including players & NPC's
 */
class Actor : public GameObject {
public:
  /*!
   * Base constructor for characters' registration
   * @param[in]  core Reference to the game core.
   * @param[in]  id  Character's identification number
   * \public \memberof Actor
   */
  Actor(Game& core, int id) : GameObject(core, id) {};

  /*!
   * Prohibit copying objects
   */
  Actor(const Actor&) = delete;
  Actor& operator =(const Actor&) = delete;
  
  /*!
   * Destructor
   * \brief Frees input
   * \pure \public \memberof Actor
   */
  virtual ~Actor() {
    if (input)
      input->assign(GameObject::InvalidObject);
  };
  
  /*!
   * Determine, which input method will be used to control the player's character
   * @param[in] in  Input method
   * \pure \public \memberof Actor
   */
  virtual void setInputMethod(SPtr<InputMethod> in) { input = in; }

  /*!
   * \fn virtual void boostBombCount(int newCount, int durationTicks) = 0;
   * \brief Increase the number of bombs
   * \pure \public \memberof Actor
   * @param[in] newCount New number of bombs
   * @param[in] durationTicks Boost's duration
   */
  virtual void boostBombCount(int newCount, int durationTicks) = 0;
  /*!
   * \fn virtual void boostBombRadius(int newVal, int durationTicks) = 0;
   * \brief Boosts bomb's radius
   * \pure \public \memberof Actor
   * @param[in] newVal New bomb's radius
   * @param[in] durationTicks Boost's duration
  */
  virtual void boostBombRadius(int newVal, int durationTicks) = 0;
  /*!
   * \fn virtual void boostInvul(int durationTicks) = 0;
   * \brief Makes the character invulnerable to bombs 
   * \pure \public \memberof Actor
   * @param[in] durationTicks Boost's duration
   */
  virtual void boostInvul(int durationTicks) = 0;
  /*!
   * \fn virtual void boostSpeed(int newVal, int durationTicks) = 0;
   * \brief Accelerate bombs' speed 
   * \pure \public \memberof Actor
   * @param[in] newVal New speed's value
   * @param[in] durationTicks Boost's duration
   */
  virtual void boostSpeed(int newVal, int durationTicks) = 0;
protected:
  /*!
   * \var SPtr<InputMethod> input
   * The input method's type
   * \protected \memberof Actor
  */
  SPtr<InputMethod> input;
};

#endif
