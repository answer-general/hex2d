#include <curses.h>
#include <panel.h>
#include "../Game.hpp"
#include "GameScreen.hpp"

class GameScreen::Private {
public:
  Private(Game& c) : core(c) {};

  void createWindow();

  Game& core;

  PANEL* panel;
  WINDOW* win;
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
}

GameScreen::~GameScreen() {
  hide_panel(d->panel);

  delwin(d->win);
}

void GameScreen::handleInput(int kbdIn) {

}

void GameScreen::draw() {

}

void GameScreen::erase() {

}
