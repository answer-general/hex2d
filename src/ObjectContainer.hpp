#ifndef OBJECTCONTAINER_HPP
#define OBJECTCONTAINER_HPP

#include "commons.hpp"

class GameObject;

class ObjectContainer {
public:
  ObjectContainer();

  // Disable incorrect automatic constructors.
  ObjectContainer(const ObjectContainer&) = delete;
  ObjectContainer& operator =(const ObjectContainer&) = delete;

  ~ObjectContainer();

  bool addObject(SPtr<GameObject>);
  SPtr<GameObject> getObject(int id);
private:
  class Private;
  UPtr<Private> d;
};

#endif
