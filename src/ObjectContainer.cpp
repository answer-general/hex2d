#include "ObjectContainer.hpp"
#include "GameObject.hpp"
#include <algorithm>
#include <map>
#include <vector>

class ObjectContainer::Private {
public:
  Private() : objects() {};

  std::map<int, SPtr<GameObject> > objects;
};

ObjectContainer::ObjectContainer() : d(new Private()) {}

ObjectContainer::~ObjectContainer() {}

bool ObjectContainer::addObject(SPtr<GameObject> obj) {
  auto state = d->objects.insert(
    std::pair<int, SPtr<GameObject> >(obj->getId(), obj));
  return state.second;
}

bool ObjectContainer::removeObject(int id) {
  auto it = d->objects.find(id);
  
  if (it == d->objects.end())
    return false;

  // And delete it from the storage.
  d->objects.erase(it);
  return true;
}

void ObjectContainer::clear() {
  d->objects.clear();
}

SPtr<GameObject> ObjectContainer::getObject(int id) {
  return d->objects.at(id);
}

std::vector<int> ObjectContainer::getAllIds() const {
  std::vector<int> res;

  for (const auto& x : d->objects)
    res.push_back(x.first);
  return res;
}

std::vector<int> ObjectContainer::getIdsIn(
    const Point& topLeft, const Point& bottomRight) const {
  std::vector<int> res;

  for (const auto& x : d->objects) {
    Point pos = x.second->pos();
    if ((pos.x >= topLeft.x && pos.x <= bottomRight.x) &&
        (pos.y >= topLeft.y && pos.y <= bottomRight.y))
      res.push_back(x.first);
  }

  return res;
}
