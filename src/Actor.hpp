#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "commons.hpp"
#include "GameObject.hpp"

class Game;
class InputMethod;

class Actor : public GameObject {
public:
  Actor(Game&);

  Actor(const Actor&) = delete;
  Actor& operator =(const Actor&) = delete;

  ~Actor();

  void setInputMethod(SPtr<InputMethod>);

  void update();

  // Property modificators for bonuses.
private:
  class Private;
  UPtr<Private> d;
};

#endif
