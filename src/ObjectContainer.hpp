#ifndef OBJECTCONTAINER_HPP
#define OBJECTCONTAINER_HPP

#include "commons.hpp"
#include <vector>

class GameObject;

class ObjectContainer {
public:
  ObjectContainer();

  // Disable incorrect automatic constructors.
  ObjectContainer(const ObjectContainer&) = delete;
  ObjectContainer& operator =(const ObjectContainer&) = delete;

  ~ObjectContainer();

  bool addObject(SPtr<GameObject>);
  bool removeObject(int id);
  void clear();

  SPtr<GameObject> getObject(int id);

  std::vector<int> getAllIds() const;
  std::vector<int> getIdsAt(const Point&) const;
private:
  class Private;
  UPtr<Private> d;
};

#endif
