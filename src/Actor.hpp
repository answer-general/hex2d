#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "commons.hpp"
#include "GameObject.hpp"

class Game;
class InputMethod;

class Actor : public GameObject {
public:
  Actor(int id) : GameObject(id) {};

  Actor(const Actor&) = delete;
  Actor& operator =(const Actor&) = delete;

  virtual ~Actor() {};

  virtual void setInputMethod(SPtr<InputMethod> in) { input = in; };
  
  virtual bool explodable() const { return true; };
  virtual bool passable() const { return false; };

  // Behaviour modification.
  virtual void explode() = 0;

  // Property modificators for bonuses.
  
protected:
  SPtr<InputMethod> input;
};

#endif
