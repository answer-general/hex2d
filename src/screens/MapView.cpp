#include <ncurses.h>
#include <vector>
#include "../Game.hpp"
#include "../GameObject.hpp"
#include "../Level.hpp"
#include "../ObjectContainer.hpp"
#include "MapView.hpp"

class MapView::Private {
public:
  Private(Game& c, WINDOW* vp) : core(c), actor(0), viewport(vp) {};

  void printLevelMap();
  void printDynamic();

  Game& core;
  int actor;
  WINDOW* viewport;
};

void MapView::Private::printLevelMap() {
  const SPtr<Level> field = core.getLevel();

  Point portSize;
  getmaxyx(viewport, portSize.y, portSize.x);

  Point fieldSize = field->getSize();

  Point pos;
  for (pos.y = 0; pos.y < portSize.x && pos.y < fieldSize.y; ++pos.y) {
    for (pos.x = 0; pos.x < portSize.x && pos.x < fieldSize.x; ++pos.x) {
      int ch = field->print(pos);
      mvwaddch(viewport, pos.y, pos.x, ch);
    }
  }
}

void MapView::Private::printDynamic() {
  Point portSize;
  getmaxyx(viewport, portSize.y, portSize.x);

  SPtr<ObjectContainer> objects = core.getObjects();

  std::vector<int> objIds = objects->getAllIds();

  for (auto x : objIds) {
    const auto o = objects->getObject(x);
    int ch = o->print();
    Point p = o->pos();

    if (p.x <= portSize.x && p.y <= portSize.y)
      mvwaddch(viewport, p.y, p.x, ch);
  }

  // Redraw actor on top.
  try {
    const auto tmp = objects->getObject(actor);

    Point tp = tmp->pos();
    int ch = tmp->print();

    mvwaddch(viewport, tp.y, tp.x, ch);
    wmove(viewport, tp.y, tp.x); // Highlight with cursor.
  } catch (const std::out_of_range&) { // Actor destroyed.
    Point port;
    getmaxyx(viewport, port.y, port.x);
    Point field = core.getLevel()->getSize();

    Point pos;
    pos.x = (port.x < field.x) ? port.x / 2 : field.x / 2;
    pos.x -= 5; // strlen("Game over") / 2;
    pos.y = (port.y < field.y) ? port.y / 2 : field.y / 2;

    mvwaddstr(viewport, pos.y, pos.x, "Game over");
  }
}

MapView::MapView(Game& core, WINDOW* vp) : d(new Private(core, vp)) {}

MapView::~MapView() {
  delwin(d->viewport);
}

void MapView::setViewport(WINDOW* vp) {
  delwin(d->viewport);
  d->viewport = vp;
}

int MapView::getActor() const {
  return d->actor;
}

void MapView::setActor(int id) {
  d->actor = id;
}

void MapView::update() {
  if (d->viewport) {
    wclear(d->viewport);
    d->printLevelMap();
    d->printDynamic();
    wnoutrefresh(d->viewport);
  }
}
