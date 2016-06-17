#ifndef SCREEN_H
#define SCREEN_H

#include "../commons.hpp"
#include <curses.h>

const int UP_CODE = KEY_UP;
const int DOWN_CODE = KEY_DOWN;
const int BACKSPACE_CODE = 127;
const int ENTER_CODE = '\r';

class Game;

class Screen {
public:
  Screen() {};
  virtual ~Screen() {};
  
  virtual void handleInput(int) = 0;
  virtual void draw() = 0;
  virtual void erase() = 0;
};

#endif
