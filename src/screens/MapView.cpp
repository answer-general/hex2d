#include <ncurses.h>
#include <map>

#include "../Game.hpp"
#include "../GameObject.hpp"
#include "../Level.hpp"
#include "MapView.hpp"

class MapView::Private {
public:
  Private(Game& c, WINDOW* vp) : core(c), viewport(vp) {};
  static int getSymbol(int id);
  void printLevelMap();

  Game& core;
  WINDOW* viewport;
};

int MapView::Private::getSymbol(int id) {
  int res;
  if (id == GameObject::TileWood)
    res = '+';
  else if (id == GameObject::TileStone)
    res = '#';
  else if (id == GameObject::TileFloor)
    res = ' ';
  else if (GameObject::idIsActor(id))
    res = '0' + id - GameObject::ActorMinId;
  else
    res = '?';

  return res;
}

void MapView::Private::printLevelMap() {
  const SPtr<Level> field = core.getLevel();

  Point portSize;
  getmaxyx(viewport, portSize.y, portSize.x);

  Point fieldSize = field->getSize();

  Point pos;
  for (pos.y = 0; pos.y < portSize.x && pos.y < fieldSize.y; ++pos.y) {
    for (pos.x = 0; pos.x < portSize.x && pos.x < fieldSize.x; ++pos.x) {
      int ch = getSymbol(field->getTopObjectAt(pos));
      mvwaddch(viewport, pos.y, pos.x, ch);
    }
  }
}

MapView::MapView(Game& core, WINDOW* vp) : d(new Private(core, vp)) {}

MapView::~MapView() {}

void MapView::setViewport(WINDOW* vp) {
  d->viewport = vp;
}

void MapView::update() {
  if (d->viewport) {
    d->printLevelMap();
    wnoutrefresh(d->viewport);
  }
}
