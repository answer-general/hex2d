#include "ObjectContainer.hpp"
#include "GameObject.hpp"
#include <algorithm>
#include <map>
#include <vector>

class ObjectContainer::Private {
public:
  Private() : objects(), places() {};

  std::map<int, SPtr<GameObject> > objects;
  std::map< Point, std::vector<int> > places;
};

ObjectContainer::ObjectContainer() : d(new Private()) {}

ObjectContainer::~ObjectContainer() {}

bool ObjectContainer::addObject(SPtr<GameObject> obj) {
  auto state = d->objects.insert(
    std::pair<int, SPtr<GameObject> >(obj->getId(), obj));
  if (state.second) { // Object wasn't there, insert into places cache.
    std::vector<int> tmp;

    auto it = d->places.find(obj->pos());

    if (it != d->places.end())
      tmp = it->second;

    tmp.push_back(obj->getId());

    d->places[obj->pos()] = tmp;

    return true;
  }

  return false;
}

bool ObjectContainer::removeObject(int id) {
  auto it = d->objects.find(id);
  
  if (it == d->objects.end())
    return false;

  // Delete object from places cache.
  Point pos = it->second->pos();
  auto kt = d->places.find(pos);

  auto mt = std::find_if(kt->second.begin(), kt->second.end(),
      [id](int v) { return v == id; });
  kt->second.erase(mt); 

  // And delete it from the storage.
  d->objects.erase(it);
  return true;
}

void ObjectContainer::clear() {
  d->objects.clear();
  d->places.clear();
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

std::vector<int> ObjectContainer::getIdsAt(const Point& pos) const {
  std::vector<int> res;

  auto it = d->places.find(pos);
  if (it != d->places.end())
    res = it->second;

  return res;
}
