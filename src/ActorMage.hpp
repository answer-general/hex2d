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

  int print() const;

  bool alive() const;
  bool kill();
 
  void update();
  void onStackWith(int);

  // Bonus effects -- provide temporary boosts.
  void boostBombCount(int newCount, int durationTicks);
  void boostBombRadius(int newVal, int durationTicks);
  void boostInvul(int durationTicks);
  void boostSpeed(int newVal, int durationTicks);
private:
  class Private;
  UPtr<Private> d;
};

#endif
