#ifndef ACTOR_MAGE_HPP
#define ACTOR_MAGE_HPP

#include "commons.hpp"
#include "Actor.hpp"

class ActorMage : public Actor {
public:
  ActorMage(Game&, int);

  ActorMage(const ActorMage&) = delete;
  ActorMage& operator =(const ActorMage&) = delete;

  ~ActorMage();

  void update();
private:
  class Private;
  UPtr<Private> d;
};

#endif
