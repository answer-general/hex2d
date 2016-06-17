#include <array>
#include <panel.h>
#include "UI.hpp"
#include "Game.hpp"
#include "screens/Screen.hpp"
#include "screens/MainMenu.hpp"
#include "screens/LevelSelect.hpp"

typedef void (* callback)(void*);

static void onLevelSelSingleEnter(void*);
static void onLevelSelSingleExit(void*);

class UI::Private {
public:
  Private(Game& g) : game(g) {};

  Game& game;

  class Transition {
  public:
    enum UI::ScreenType type;
    callback onEnter; // For special operations.
    callback onExit; // For special operations.
    SPtr<Screen> screen;
  };

  std::array< Transition, (size_t)UI::ScreensCount > screens;
  enum UI::ScreenType currentScreen;
};

UI::UI(Game& g) : d(new Private(g)) {
  Private::Transition mainMenu = {
    UI::MainMenuScreen,
    nullptr,
    nullptr,
    SPtr<Screen>(new MainMenu(d->game))
  };

  SPtr<Screen> levelSelector(new LevelSelect(d->game));
  Private::Transition levelSelSingle = {
    UI::LevelSelSingle,
    onLevelSelSingleEnter,
    onLevelSelSingleExit,
    levelSelector
  };
  
  d->screens[(int)mainMenu.type] = mainMenu;
  d->screens[(int)levelSelSingle.type] = levelSelSingle;

  d->currentScreen = mainMenu.type;

  d->screens[(int)d->currentScreen].screen->draw();
  update_panels();
  doupdate();
}

UI::~UI() {}

void UI::update() {
  // Peek at the keyboard input.
  int kbdIn = getch();
  ungetch(kbdIn);

  d->screens[d->currentScreen].screen->handleInput(kbdIn);
  d->screens[d->currentScreen].screen->draw();
  update_panels();
  doupdate();
}

void UI::switchScreen(enum ScreenType target) {
  if (target == NoScreen) { // Request to shutdown.
    d->game.setState(Game::GameStopped);
  } else { // Change screens.
    if (d->screens[d->currentScreen].onExit)
      d->screens[d->currentScreen].onExit(d->screens[d->currentScreen].screen.get());
    d->screens[d->currentScreen].screen->erase();

    d->currentScreen = target;

    if (d->screens[d->currentScreen].onEnter)
      d->screens[d->currentScreen].onEnter(d->screens[d->currentScreen].screen.get());
    d->screens[d->currentScreen].screen->draw();
  }
}

static void onLevelSelSingleEnter(void* scr) {
  LevelSelect* ls = (LevelSelect*)scr;
  ls->setMode(LevelSelect::SinglePlayer);
}

static void onLevelSelSingleExit(void* scr) {
  LevelSelect* ls = (LevelSelect*)scr;
  ls->setMode(LevelSelect::DefaultMode);
}
