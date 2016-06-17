#ifndef MAP_VIEW_HPP
#define MAP_VIEW_HPP

#include <ncurses.h>
#include "../commons.hpp"

class Game;

class MapView {
public:
  MapView(Game& core, WINDOW* origin = nullptr);

  MapView(const MapView&) = delete;
  MapView& operator =(const MapView&) = delete;

  ~MapView();

  void setOrigin(WINDOW* origin);

  void update();
private:
  class Private;
  UPtr<Private> d;
};

#endif
