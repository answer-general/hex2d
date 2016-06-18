#ifndef UI_HPP
#define UI_HPP

#include "commons.hpp"

class Game;

class UI {
public:
  enum ScreenType {
    MainMenuScreen,
    LevelSelSingle,
    GameSingle,
    ScreensCount,
    NoScreen // Signals shutdown.
  };

  UI(Game&);

  UI(const UI&) = delete;
  UI& operator =(const UI&) = delete;

  ~UI();

  void update();

  void switchScreen(enum ScreenType);
private:
  class Private;
  UPtr<Private> d;
};

#endif
