#include <array>
#include <curses.h>
#include <menu.h>
#include <panel.h>
#include <string>
#include "../Game.hpp"
#include "../UI.hpp"
#include "MainMenu.hpp"

class MainMenu::Private {
public:
  Private(Game& core) : core(core) {};
  void createWindow();
  void createMenu();
  void selectItem(int);

  static const size_t titlesSize = 6;
  static const std::array<const std::string, titlesSize> titles;

  Game& core;
  // Add one item for "NULL-terminator".
  std::array<ITEM*, titlesSize + 1> entries;
  PANEL* panel; // For stack window management.
  WINDOW* win;
  WINDOW* subwindow; // Required by menu library.
  MENU* menu;
  bool shown;
};

const std::array<const std::string, MainMenu::Private::titlesSize>
    MainMenu::Private::titles = {
  std::string("Single player"),
  std::string("Hot seat"),
  std::string("Host networked game"),
  std::string("Connect to networked game"),
  std::string("Settings"),
  std::string("Exit")
};

void MainMenu::Private::createWindow() {
  // Create full-screen window.
  int y, x;
  getmaxyx(stdscr, y, x);
  win = newwin(y, x, 0, 0);
  subwindow = subwin(win, y, x, 0, 0);

  // Create panel.
  panel = new_panel(win);
  // Hide by default.
  bottom_panel(panel);
}

void MainMenu::Private::createMenu() {
  for (size_t i = 0; i < entries.size(); ++i)
    entries[i] = new_item(titles[i].c_str(), NULL);
  entries[entries.size()] = NULL; // Add NULL-termination.

  menu = new_menu(entries.data());

  set_menu_win(menu, win);
  set_menu_sub(menu, subwindow);

  post_menu(menu);
}

void MainMenu::Private::selectItem(int idx) {
  if (titles[idx] == "Single player") {
    core.getUI()->switchScreen(UI::LevelSelSingle);
  } else if (titles[idx] == "Exit") {
    core.getUI()->switchScreen(UI::NoScreen);
  }
}

MainMenu::MainMenu(Game& core) : d(new Private(core)) {
  d->createWindow();
  d->createMenu();
  d->shown = false;
}

MainMenu::~MainMenu() {
  hide_panel(d->panel); // Delete from screen stack.

  unpost_menu(d->menu);
  free_menu(d->menu);

  delwin(d->subwindow);
  delwin(d->win);
  del_panel(d->panel);

  for (size_t i = 0; i < d->entries.size() - 1; ++i)
    free_item(d->entries[i]);
}

void MainMenu::handleInput(int in) {
  ITEM* curItem;

  switch (in) {
  case UP_CODE:
    menu_driver(d->menu, REQ_UP_ITEM);
    break;
  case DOWN_CODE:
    menu_driver(d->menu, REQ_DOWN_ITEM);
    break;
  case BACKSPACE_CODE: // Detect Backspace and quit.
    d->core.getUI()->switchScreen(UI::NoScreen);
    break;
  case ENTER_CODE: // Switch screens.
    curItem = current_item(d->menu);
    d->selectItem(item_index(curItem));
    break;
  default:
    break;
  };
}

void MainMenu::draw() {
  if (!d->shown) {
    top_panel(d->panel);
    d->shown = true;
  }
}

void MainMenu::erase() {
  if (d->shown) {
    bottom_panel(d->panel);
    d->shown = false;
  }
}
