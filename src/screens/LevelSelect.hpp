#ifndef LEVEL_SELECT_HPP
#define LEVEL_SELECT_HPP

#include "../commons.hpp"
#include "Screen.hpp"

class Game;

class LevelSelect : public Screen {
public:
  enum Mode {
    SinglePlayer,
    HotSeat,
    NetworkHost,
    DefaultMode
  };

  LevelSelect(Game& core);

  LevelSelect(const LevelSelect&) = delete;
  LevelSelect& operator =(const LevelSelect&) = delete;

  ~LevelSelect();

  // Affects outgoing transitions.
  void setMode(enum Mode);

  void handleInput(int);
  void draw();
  void erase();
private:
  class Private;
  UPtr<Private> d;
};

#endif
