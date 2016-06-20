#ifndef ACTOR_IMP_HPP
#define ACTOR_IMP_HPP

#include "commons.hpp"
#include "Actor.hpp"

class ActorImp : public Actor {
public:
  ActorImp(Game&, int);

  ActorImp(const ActorImp&) = delete;
  ActorImp& operator =(const ActorImp&) = delete;

  ~ActorImp();

  int print() const;

  bool alive() const;
  bool kill();
 
  void update();
  void onStackWith(int id);

  // Stubs -- don't affect behaviour.
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
