#include <array>
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
  static const int maxSplit = 2;

  Private(Game& c) : core(c), panel(nullptr), win(nullptr),
      gameArea(), shown(false) {};

  void createWindow();
  void prepareMap();

  Game& core;

  PANEL* panel;
  WINDOW* win;
  std::array< UPtr<MapView>, maxSplit> gameArea;
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

void GameScreen::Private::prepareMap() {
  SPtr<Engine> e = core.getEngine();

  if (e->getMode() == Engine::ModeSingle) { // Create only one screen.
    WINDOW* vp = subwin(win, 0, 0, 0, 0); // Full-screen port.

    gameArea[0].reset(new MapView(core, vp));
    gameArea[0]->setActor(core.getPlayer1Id());
  } else if (e->getMode() == Engine::ModeHotseat) { // Split screen by two.
    int y, x;
    getmaxyx(win, y, x);

    WINDOW* vp1 = subwin(win, y / 2, x / 2, 0, 0); // Take half of screen.
    WINDOW* vp2 = subwin(win, 0, 0, 0, x / 2); // Occupy the rest.

    gameArea[0].reset(new MapView(core, vp1));
    gameArea[1].reset(new MapView(core, vp2));
    gameArea[0]->setActor(core.getPlayer1Id());
    gameArea[1]->setActor(core.getPlayer2Id());
  }
}

GameScreen::GameScreen(Game& core) : d(new Private(core)) {
  d->createWindow();
}

GameScreen::~GameScreen() {
  hide_panel(d->panel);

  for (auto it = d->gameArea.begin(); it != d->gameArea.end(); ++it)
    it->reset();

  delwin(d->win);
  del_panel(d->panel);
}

void GameScreen::handleInput(int kbdIn) {
  switch (kbdIn) {
  case BACKSPACE_CODE:
    d->core.getEngine()->stop();
    d->core.getUI()->switchScreen(UI::MainMenuScreen);
    break;
  default:
    break;
  };
}

void GameScreen::draw() {
  if (!d->shown) {
    d->prepareMap();

    top_panel(d->panel);
    d->shown = true;
  }
  for (auto it = d->gameArea.begin(); it != d->gameArea.end(); ++it)
    if (*it)
      (*it)->update();
}

void GameScreen::erase() {
  if (d->shown) {
    bottom_panel(d->panel);
    d->shown = false;
  }
}
