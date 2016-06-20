#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "commons.hpp"
#include "GameObject.hpp"
#include "InputMethod.hpp"

class Game;

class Actor : public GameObject {
public:
  Actor(int id) : GameObject(id) {};

  Actor(const Actor&) = delete;
  Actor& operator =(const Actor&) = delete;

  virtual ~Actor() {
    // Free input.
    if (input)
      input->assign(GameObject::InvalidObject);
  };

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
