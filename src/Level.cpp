#include "Config.hpp"
#include "Game.hpp"
#include "Level.hpp"
#include "Tiles.hpp"
#include "ObjectContainer.hpp"
#include <algorithm>
#include <map>
#include <stdexcept>
#include <stdio.h>
#include <utility>
#include <vector>

Cell::Cell() : used(0) {}

Cell::Cell(const Cell& o) {
  for (size_t i = 0; i < o.used; ++i)
    buffer[i] = o.buffer[i];
  used = o.used;
}

Cell& Cell::operator =(const Cell& o) {
  for (size_t i = 0; i < o.used; ++i)
    buffer[i] = o.buffer[i];
  used = o.used;

  return *this;
}

size_t Cell::size() const { return used; }

void Cell::clear() { used = 0; }

bool Cell::back(int& res) const {
  if (used == 0)
    return false;

  res = buffer[used-1];
  return true;
}

bool Cell::push(int val) {
  if (used == MaxObjects)
    return false;

  buffer[used++] = val;
  return true;
}

bool Cell::pop() {
  if (used == 0)
    return false;

  --used;
  return true;
}

int Cell::find(int id) const {
  size_t i;
  for (i = 0; i < used; ++i)
    if (buffer[i] == id)
      break;

  if (i == used)
    return -1;

  return i; 
}

bool Cell::erase(size_t idx) {
  if (idx > used)
    return false;

  --used;
  for (size_t i = idx; i < used - 1; ++i)
    buffer[i] = buffer[i+1];

  return true;
}

class Level::Private {
public:
  Private(Game& c) : core(c), size(0, 0), field(),
      spawns(), spawnsUsed(0), idPos(), posIds() {};

  bool levelSizeFromFile(FILE* in);
  bool fieldFromFile(FILE* in);
  int& fieldAt(const Point&);
  const int& fieldAt(const Point&) const;

  Game& core;

  Point size;
  std::vector<int> field;

  // Spawn points.
  std::vector<Point> spawns;
  size_t spawnsUsed;

  // Dynamic objects lookup structures.
  std::map<int, Point> idPos;
  std::map<Point, Cell> posIds;

//  // Efficient due to relatively small objects count.
//  std::vector< std::pair< Cell, Point > > cells;
};

Level::Level(Game& core) : d(new Private(core)) {
}

Level::~Level() {

}

const Point& Level::getSize() const {
  return d->size;
}

int Level::getTopObjectAt(const Point& pos) const {
  if (pos.x >= d->size.x || pos.y >= d->size.y) {
    return GameObject::InvalidObject;
  }

  return d->fieldAt(pos);
}

Cell Level::getCellAt(const Point& pos) const {
  Cell res;
  
  if (pos.x >= d->size.x || pos.y >= d->size.y) {
    res.push(GameObject::InvalidObject);
  } else {
    auto it = d->posIds.find(pos);
    if (it == d->posIds.end())
      res.push(GameObject::InvalidObject);
    else
      res = it->second;
  }

  return res;
}

Point Level::getObjectPos(int id) const {
  auto it = d->idPos.find(id);
  if (it == d->idPos.end())
    throw std::out_of_range("Id not found" + std::to_string(id));

  return it->second;
}

bool Level::spawn(int objId) {
  // All spawners occupied.
  if (d->spawnsUsed == d->spawns.size())
    return false;

  if (!placeAt(objId, d->spawns[d->spawnsUsed]))
    return false;

  ++d->spawnsUsed;

  return true;
}

bool Level::moveTo(int id, const Point& pos) {
  if (pos.x >= d->size.x || pos.y >= d->size.y)
    return false;

  // Find old location.
  auto it = d->idPos.find(id);
  if (it == d->idPos.end()) // Object not on field.
    return false;

  Point oldLoc = it->second;

  // Get cell at new location.
  auto kt = d->posIds.find(pos);
  Cell c;
  if (kt == d->posIds.end()) { // Not found, create.
    c.push(d->fieldAt(pos));
  } else {
    c = kt->second;
  }

  // Check, if we can step on the new cell.
  int tmp;
  c.back(tmp);
  if (!d->core.getObjects()->getObject(tmp)->passable())
    return false;

  // Remove id from the old cell and place to new.
  kt = d->posIds.find(oldLoc);
  if (kt != d->posIds.end()) {
    // Remove id from cell.
    int idx = kt->second.find(id);
    kt->second.erase(idx);

    // Find new top.
    int tmp;
    kt->second.back(tmp);
    d->fieldAt(oldLoc) = tmp;

    // Only one element left -> cell unneeded.
    if (kt->second.size() == 1)
      d->posIds.erase(kt);
  }

  d->idPos[id] = pos;

  c.push(id);
  d->posIds[pos] = c;
  d->fieldAt(pos) = id;

  return true;
}

// Warning! Doesn't check for walls!
bool Level::placeAt(int id, const Point& pos) {
  if (pos.x >= d->size.x || pos.y >= d->size.y)
    return false;

  // Get cell.
  Cell c = d->posIds[pos];
  // Push current top cell if empty.
  if (c.size() == 0)
    c.push(d->fieldAt(pos));

  // Place new top.
  d->idPos[id] = pos;

  c.push(id);
  d->posIds[pos] = c;
  
  int tmp;
  c.back(tmp);
  d->fieldAt(pos) = tmp;

  return true;
}

bool Level::fromFile(const std::string& name) {
  std::string path = d->core.getConfig()->getLevelsPath();
  path += name;
  path += ".hml";

  FILE* in = fopen(path.c_str(), "r");
  if (!in)
    return false;

  if (!d->levelSizeFromFile(in)) {
    fclose(in);
    return false;
  }

  if (!d->fieldFromFile(in)) {
    fclose(in);
    return false;
  }

  fclose(in);
  return true;
}

void Level::reset() {
  d->field.clear();
  d->field.shrink_to_fit();
  d->size = {0, 0};

  d->spawns.clear();
  d->spawns.shrink_to_fit();
  d->spawnsUsed = 0;

//  d->cells.clear();
//  d->cells.shrink_to_fit();
}

bool Level::Private::levelSizeFromFile(FILE* in) {
  size = {0, 0};

  size_t inPos = ftell(in);

  fseek(in, 0, SEEK_SET);
  
  char c;
  while ((c = fgetc(in)) != '\n')
    ++size.x;
  
  fseek(in, 0, SEEK_END);
  size.y = ftell(in) / (size.x + 1); // Account for newlines.
  
  fseek(in, inPos, SEEK_SET);
  
  return (size.x != 0) && (size.y != 0);
}

bool Level::Private::fieldFromFile(FILE* in) {
  field.resize(size.x * size.y, 0);

  // Get tiles.
  int wood = GameObject::TileWood;
  int stone = GameObject::TileStone;
  int floor = GameObject::TileFloor;

  Point read = { 0, 0 };

  for (read.y = 0; read.y < size.y; ++read.y) {
    for (read.x = 0; read.x < size.x + 1; ++read.x) {
      char c = fgetc(in);

      switch (c) {
      case EOF: // Error: file is too short.
        return false;
        break;
      case '\n': // End of line, read next.
        if (read.x < size.x)
          return false;
        continue;
        break;
      case '+':
        fieldAt(read) = wood;
        break;
      case '#':
        fieldAt(read) = stone;
        break;
      case '@': // Spawner. Just a special floor cell.
        spawns.push_back(read);
      case ' ':
        fieldAt(read) = floor;
        break;
      };
    }
  }

  return true;
}

int& Level::Private::fieldAt(const Point& p) {
  return field[p.y * size.x + p.x];
}

const int& Level::Private::fieldAt(const Point& p) const {
  return field[p.y * size.x + p.x];
}
