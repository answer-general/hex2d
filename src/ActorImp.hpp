/**
 * \file ActorImp.hpp
 */
#ifndef ACTOR_IMP_HPP
#define ACTOR_IMP_HPP

#include "commons.hpp"
#include "Actor.hpp"

/*!
 * \class ActorImp
 * \brief - class for non-player characters (NPC)
 *  Class for all NPC's
 */
class ActorImp : public Actor {
public:
  /*!
   * Base constructor for characters' registration
   * @param[in]  core Reference to the game core.
   * @param[in]  id  Character's identification number
   * \public \memberof ActorImp
   */
  ActorImp(Game&, int);
  /*!
   * Prohibit copying objects
   */
  ActorImp(const ActorImp&) = delete;
  ActorImp& operator =(const ActorImp&) = delete;
  /*!
   * Destructor
   * \public \memberof ActorImp
   */
  ~ActorImp();

  /*!
   * \fn int print() const
   * \brief Returns NPC's icon(letter): '@'
   * \public \memberof ActorImp
   */
  int print() const;
  /*!
   * \fn bool alive() const
   * \brief Return NPC's state: alive or not alive
   * \public \memberof ActorImp
   */
  bool alive() const;
  /*!
   * \fn bool kill()
   * \brief Kills NPC
   * \public \memberof ActorImp
   * If NPC is alive, function kills it. Then return NPC's state.
   */
  bool kill();
 
  /*!
   * \fn void update()
   * \brief Updates NPC's position
   * \public \memberof ActorImp
   */
  void update();
  /*!
   * \fn void onStackWith(int id)
   * \brief Attack enemies & kill mages
   * \public \memberof ActorImp
   * @param[in] id Enemies identification number
   */
  void onStackWith(int id);
private:
  class Private;
  UPtr<Private> d;
};

#endif
