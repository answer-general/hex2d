#include <curses.h>
#include "MapView.hpp"

class MapView::Private {
public:
  Private(Game& c) : core(c) {};
  void printLevelMap();

  Game& core;
  WINDOW* origin;

  WINDOW* displayArea;
};

void MapView::Private::printLevelMap() {

}

MapView::MapView(Game& core, WINDOW* origin) : d(new Private(core)) {
  d->origin = origin;

  if (d->origin) { // Create pad, if possible.
    int y, x;
    getmaxyx(d->origin, y, x);

    d->displayArea = subpad(d->origin, y, x, 0, 0);
  } else {
    d->displayArea = nullptr;
  }
}

MapView::~MapView() {
  delwin(d->displayArea);
}

void MapView::setOrigin(WINDOW* origin) {
  if (origin) {
    delwin(d->displayArea);

    d->origin = origin;

    int y, x;
    getmaxyx(d->origin, y, x);

    d->displayArea = subpad(d->origin, y, x, 0, 0);
  }
}

void MapView::update() {
  if (d->displayArea) {
    d->printLevelMap();

    // Print pad segment to window.
    int y, x;
    getmaxyx(d->origin, y, x);
    // TODO: tie parameters 3 and 4 to tracked character.
    pnoutrefresh(d->displayArea, 0, 0, 0, 0, y, x);
  }
}
