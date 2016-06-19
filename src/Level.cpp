#include "Config.hpp"
#include "Game.hpp"
#include "Level.hpp"
#include <stdio.h>
#include <vector>

class Level::Private {
public:
  enum Cell {
    Wood,
    Stone,
    Floor
  };

  Private(Game& core) : core(core), size(0,0), cells(),
      spawns(), spawnsUsed(0) {};
  bool sizeFromFile(FILE*);
  bool cellsFromFile(FILE*);
  enum Cell& cellAt(const Point&);
  const enum Cell& cellAt(const Point&) const;

  Game& core;

  Point size;
  std::vector<enum Cell> cells;

  std::vector<Point> spawns;
  size_t spawnsUsed;
};

Level::Level(Game& core) : d(new Private(core)) {
}

Level::~Level() {
}

const Point& Level::getSize() const {
  return d->size;
}

Point Level::nextSpawn() {
  if (d->spawnsUsed == d->spawns.size())
    return Point(-1, -1);
  else
    return d->spawns[d->spawnsUsed++];
}

bool Level::destroy(const Point& pos) {
  if ((pos.x >= 0) && (pos.y >= 0) && 
      (pos.x > d->size.x || pos.y > d->size.y))
    return false;

  enum Private::Cell c = d->cellAt(pos);

  if (c == Private::Wood) {
    d->cellAt(pos) = Private::Floor;
    return true;
  } else if (c == Private::Floor) { // Fire passes over floor without damaging it.
    return true;
  } else {
    return false;
  }
}

bool Level::canCross(const Point& pos) {
  if ((pos.x >= 0) && (pos.y >= 0) && 
      (pos.x > d->size.x || pos.y > d->size.y))
    return false;

  enum Private::Cell c = d->cellAt(pos);

  if (c == Private::Wood || c == Private::Stone) {
    return false;
  } else {
    return true;
  }
}

int Level::print(const Point& pos) {
  if ((pos.x >= 0) && (pos.y >= 0) && 
      (pos.x > d->size.x || pos.y > d->size.y))
    return false;

  int res;

  enum Private::Cell c = d->cellAt(pos);

  switch (c) {
  case Private::Wood:
    res = '+';
    break;
  case Private::Stone:
    res = '#';
    break;
  case Private::Floor:
    res = ' ';
    break;
  };

  return res;
}

bool Level::fromFile(const std::string& name) {
  // Reset level.
  d->cells.clear();
  d->cells.shrink_to_fit(); // Free excess memory of old level.
  d->spawns.clear();
  d->spawnsUsed = 0;

  // Open level file.
  std::string path = d->core.getConfig()->getLevelsPath();
  path += name;
  path += ".hml";

  FILE* in = fopen(path.c_str(), "r");
  if (!in)
    return false;

  // Calculate map size.
  if (!d->sizeFromFile(in)) {
    fclose(in);
    return false;
  }

  // Load map contents.
  if (!d->cellsFromFile(in)) {
    fclose(in);
    return false;
  }

  fclose(in);
  return true;
}

bool Level::Private::sizeFromFile(FILE* in) {
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

bool Level::Private::cellsFromFile(FILE* in) {
  cells.resize(size.x * size.y, Private::Floor);

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
        cellAt(read) = Private::Wood;
        break;
      case '#':
        cellAt(read) = Private::Stone;
        break;
      case '@': // Spawner. Just a special floor cell.
        spawns.push_back(read);
      case ' ':
        cellAt(read) = Private::Floor;
        break;
      };
    }
  }

  return true;
}

enum Level::Private::Cell& 
    Level::Private::cellAt(const Point& p) {
  return cells[p.y * size.x + p.x];
}

const enum Level::Private::Cell& 
    Level::Private::cellAt(const Point& p) const {
  return cells[p.y * size.x + p.x];
}
