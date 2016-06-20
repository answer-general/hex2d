/*!
 * \file ObjectContainer.hpp
 */
#ifndef OBJECTCONTAINER_HPP
#define OBJECTCONTAINER_HPP

#include "commons.hpp"
#include <vector>

class GameObject;
/*
 * \class GameObject
 * Keeps all objects in the game.
 */
class ObjectContainer {
public:
  /*!
   * Object container constructor.
   * \public \memberof ObjectContainer
   */
  ObjectContainer();

  /*!
   * Disable incorrect automatic constructors.
   */
  ObjectContainer(const ObjectContainer&) = delete;
  ObjectContainer& operator =(const ObjectContainer&) = delete;

  ~ObjectContainer();
  /*!
   * \fn bool addObject(SPtr<GameObject> newObj)
   * Adds new object.
   * param[in] newObj New object.
   * \public \memberof ObjectContainer
   */
  bool addObject(SPtr<GameObject>);
  /*!
   * \fn bool removeObject(int id)
   * Remove object with identification number = id.
   * param[in] id Identification number of the object, that will be removed.
   * \public \memberof ObjectContainer
   */
  bool removeObject(int id);
  /*!
   * \fn void clear()
   * Remove all objects
   * \public \memberof ObjectContainer
   */
  void clear();
  /*!
   * \fn SPtr<GameObject> getObject(int id)
   * Return object with identification number = id.
   * \public \memberof ObjectContainer
   */
  SPtr<GameObject> getObject(int id);
  /*!
   * \fn std::vector<int> getAllIds() const
   * Return all available id's.
   * \public \memberof ObjectContainer
   */
  std::vector<int> getAllIds() const;
  /*!
   * \fn std::vector<int> getIdsIn(const Point& topleft, const Point& bottomright) const
   * Return all objects's ids, from top left to bottom right position on the level.
   * @param[in] topleft Top left position.
   * @param[in] bottomright Bottom right position.
   * \public \memberof ObjectContainer
   */
  std::vector<int> getIdsIn(const Point&, const Point&) const;
  
  void update();
private:
  class Private;
  UPtr<Private> d;
};

#endif
