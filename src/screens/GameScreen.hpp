#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include "../commons.hpp"
#include "Screen.hpp"

class Game;

class GameScreen : public Screen {
public:
  GameScreen(Game&);

  GameScreen(const GameScreen&) = delete;
  GameScreen& operator =(const GameScreen&) = delete;

  ~GameScreen();

  void handleInput(int);
  void draw();
  void erase();
private:
  class Private;
  UPtr<Private> d;
};

#endif
