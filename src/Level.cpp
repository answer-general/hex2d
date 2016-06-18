#include "Config.hpp"
#include "Game.hpp"
#include "Level.hpp"
#include "Tiles.hpp"
#include "ObjectContainer.hpp"
#include <algorithm>
#include <stdexcept>
#include <stdio.h>
#include <vector>

class Level::Private {
public:
  Private(Game& c) : core(c),
    size(0, 0), field(), spawns(), spawnsUsed(0), objects() {};

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

  // For retaining backgrounds of cells under dynamic objects.
  struct Cell {
    int fore;
    int back;
    Point pos;
  };
  // Efficient due to relatively small objects count.
  std::vector<Cell> objects;
};

Level::Level(Game& core) : d(new Private(core)) {
}

Level::~Level() {

}

const Point& Level::getSize() const {
  return d->size;
}

int Level::getObjectAt(const Point& pos) const {
  if (pos.x > d->size.x || pos.y > d->size.y)
    return GameObject::InvalidObject;

  return d->field[pos.y * d->size.x + pos.x];
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
  { auto it = std::find_if(d->objects.begin(), d->objects.end(),
      [id](const Private::Cell& v) { return v.fore == id; });

    if (it != d->objects.end()) {
      d->fieldAt(it->pos) = it->back;
      d->objects.erase(it);
    }
  }

  // Save information about new cell.
  { Private::Cell c;
    c.fore = id;
    c.back = d->fieldAt(pos);
    c.pos = pos;

    d->objects.push_back(c);
  }

  // Add id to new cell.
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
  auto it = std::find_if(d->objects.begin(), d->objects.end(),
      [pos](const Private::Cell& v) { return v.pos == pos; });

  if (it == d->objects.end()) { // Cell not occupied, save info.
    Private::Cell c;
    c.pos = pos;
    c.back = d->fieldAt(pos);
    it = d->objects.insert(d->objects.end(), c);
  }

  it->fore = id; // Overwrite current foreground.
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

  d->objects.clear();
  d->objects.shrink_to_fit();
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
