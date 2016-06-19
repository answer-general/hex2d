#include "ObjectContainer.hpp"
#include "GameObject.hpp"
#include "Tiles.hpp"
#include <map>

class ObjectContainer::Private {
public:
  std::map<int, SPtr<GameObject> > objects;
};

ObjectContainer::ObjectContainer() : d(new Private()) {
  // Push default objects -- tiles.
  SPtr<GameObject> wood = std::make_shared<WoodTile>();
  SPtr<GameObject> stone = std::make_shared<StoneTile>();
  SPtr<GameObject> floor = std::make_shared<FloorTile>();

  d->objects.insert(std::pair<int, SPtr<GameObject> >(wood->getId(), wood));
  d->objects.insert(std::pair<int, SPtr<GameObject> >(stone->getId(), stone));
  d->objects.insert(std::pair<int, SPtr<GameObject> >(floor->getId(), floor));
}

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

  d->objects.erase(it);
  return true;
}

SPtr<GameObject> ObjectContainer::getObject(int id) {
  return d->objects.at(id);
}

void ObjectContainer::updateAll() {
  for (auto it = d->objects.begin(); it != d->objects.end(); ++it)
    it->second->update();
}
