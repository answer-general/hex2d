#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "../commons.hpp"
#include "Screen.hpp"

class Game;

class MainMenu : public Screen {
public:
  MainMenu(Game& core);
  ~MainMenu();
  
  void handleInput(int);
  void draw();
  void erase();
private:
  class Private;
  UPtr<Private> d;
};

#endif
