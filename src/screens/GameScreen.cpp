#include <ncurses.h>
#include <panel.h>
#include "../Engine.hpp"
#include "../Game.hpp"
#include "../Level.hpp"
#include "../UI.hpp"
#include "GameScreen.hpp"
#include "MapView.hpp"

class GameScreen::Private {
public:
  Private(Game& c) : core(c), panel(nullptr), win(nullptr),
      gameArea(nullptr), shown(false) {};

  void createWindow();

  Game& core;

  PANEL* panel;
  WINDOW* win;
  UPtr<MapView> gameArea;
  bool shown;
};

void GameScreen::Private::createWindow() {
  // Create full-screen window.
  int y, x;
  getmaxyx(stdscr, y, x);
  win = newwin(y, x, 0, 0);

  // Create panel.
  panel = new_panel(win);
  // Hide by default.
  bottom_panel(panel);
}

GameScreen::GameScreen(Game& core) : d(new Private(core)) {
  d->createWindow();
  // TODO: Move gameArea to subwindow.
  d->gameArea.reset(new MapView(d->core, d->win));
}

GameScreen::~GameScreen() {
  hide_panel(d->panel);
  d->gameArea.reset();
  delwin(d->win);
  del_panel(d->panel);
}

void GameScreen::handleInput(int kbdIn) {
  switch (kbdIn) {
  case BACKSPACE_CODE:
    // Stop game and go to main menu.
    // Replace with engine's reset.
    d->core.getLevel()->reset();
    d->core.getEngine()->stop();
    d->core.getUI()->switchScreen(UI::MainMenuScreen);
    break;
  default:
    break;
  };
}

void GameScreen::draw() {
  if (!d->shown) {
    top_panel(d->panel);
    d->shown = true;
  }
  d->gameArea->update();
}

void GameScreen::erase() {
  if (d->shown) {
    bottom_panel(d->panel);
    d->shown = true;
  }
}
