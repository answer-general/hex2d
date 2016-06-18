#include "Config.hpp"
#include "Game.hpp"
#include "Level.hpp"
#include "Tiles.hpp"
#include "ObjectContainer.hpp"
#include <algorithm>
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
      spawns(), spawnsUsed(0), cells() {};

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

  // Efficient due to relatively small objects count.
  std::vector< std::pair< Cell, Point > > cells;
};

Level::Level(Game& core) : d(new Private(core)) {
}

Level::~Level() {

}

const Point& Level::getSize() const {
  return d->size;
}

int Level::getTopObjectAt(const Point& pos) const {
  if (pos.x > d->size.x || pos.y > d->size.y) {
    return GameObject::InvalidObject;
  }

  return d->fieldAt(pos);
}

Cell Level::getCellAt(const Point& pos) const {
  Cell res;
  
  if (pos.x > d->size.x || pos.y > d->size.y) {
    res.push(GameObject::InvalidObject);
  } else {
    // Find if there are several objects in cell.
    auto it = std::find_if(d->cells.begin(), d->cells.end(),
        [pos](const std::pair<Cell, Point>& v)
        { return v.second == pos; });

    if (it != d->cells.end()) // Multiple objects found, copy cell.
      res = it->first;
    else // Only one object, take from field.
      res.push(d->fieldAt(pos));
  }

  return res;
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
  if (pos.x > d->size.x || pos.y > d->size.y)
    return false;
  
  try {
    d->core.getObjects()->getObject(id);
  } catch (const std::out_of_range&) {
    return false;
  };

  // Remove id from previous cell.
  { auto it = std::find_if(d->cells.begin(), d->cells.end(),
      [id](const std::pair<Cell, Point>& v)
      { return v.first.find(id) != -1; });

    // Id found.
    if (it != d->cells.end()) {
      // Take this element away.
      int idx = it->first.find(id);
      it->first.erase(idx);

      // Restore top element.
      it->first.back(d->fieldAt(it->second));

      // Only one object left, no ambiguity.
      if (it->first.size() == 1)
        d->cells.erase(it);
    }
  }

  // Add id to the new cell.
  { // Save current cell value.
    auto it = std::find_if(d->cells.begin(), d->cells.end(),
      [pos](const std::pair<Cell, Point>& v) { return v.second == pos; });

    if (it == d->cells.end()) { // Cell not occupied, save info.
      Cell c;
      c.push(d->fieldAt(pos));
      c.push(id);

      d->cells.push_back(std::pair<Cell, Point>(c, pos));
    } else { // Add id to the top.
      if (!it->first.push(id))
        return false;
    }  
  }

  // Place id on the field as well;
  d->fieldAt(pos) = id;
  return true; 
}

bool Level::placeAt(int id, const Point& pos) {
  if (pos.x > d->size.x || pos.y > d->size.y)
    return false;

  try {
    d->core.getObjects()->getObject(id);
  } catch (const std::out_of_range&) {
    return false;
  };

  // Save current cell value.
  auto it = std::find_if(d->cells.begin(), d->cells.end(),
      [pos](const std::pair<Cell, Point>& v) { return v.second == pos; });

  if (it == d->cells.end()) { // Cell not occupied, save info.
    Cell c;
    c.push(d->fieldAt(pos));
    c.push(id);

    d->cells.push_back(std::pair<Cell, Point>(c, pos));
  } else { // Add id to the top.
    if (!it->first.push(id))
      return false;
  }

  // Place id on the field as well;
  d->fieldAt(pos) = id;
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

  d->cells.clear();
  d->cells.shrink_to_fit();
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
  field.reserve(size.x * size.y);
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
