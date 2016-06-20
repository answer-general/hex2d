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
protected:
  SPtr<InputMethod> input;
};

#endif
