#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "commons.hpp"
#include "GameObject.hpp"
#include "InputMethod.hpp"

class Game;
//  Actor - base class for all game characters, including players & NPC's
class Actor : public GameObject {
public:
  // Base constructor for characters' registration
  Actor(int id) : GameObject(id) {};

  // Prohibit copying objects
  Actor(const Actor&) = delete;
  Actor& operator =(const Actor&) = delete;
  
  // Destructor
  virtual ~Actor() {
    // Free input.
    if (input)
      input->assign(GameObject::InvalidObject);
  };
  
  // Determine, which input method will be used to control the player's character
  virtual void setInputMethod(SPtr<InputMethod> in) { input = in; }

  // Bonus effects -- provide temporary boosts.
  virtual void boostBombCount(int newCount, int durationTicks) = 0;
  virtual void boostBombRadius(int newVal, int durationTicks) = 0;
  virtual void boostInvul(int durationTicks) = 0;
  virtual void boostSpeed(int newVal, int durationTicks) = 0;
protected:
  SPtr<InputMethod> input;
};

#endif
