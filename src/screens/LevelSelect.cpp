#include <curses.h>
#include <menu.h>
#include <panel.h>
#include <string>
#include <vector>
#include "../Game.hpp"
#include "../Config.hpp"
#include "../FileHelper.hpp"
#include "../UI.hpp"
#include "LevelSelect.hpp"

class LevelSelect::Private {
public:
  Private(Game& core) : core(core), mode(LevelSelect::DefaultMode),
      levelNames(), entries(), menu(nullptr), shown(false) {};

  void readLevelsList();
  void createWindow();
  void createMenu();
  void selectItem(int);

  Game& core;
  enum LevelSelect::Mode mode;

  std::vector<std::string> levelNames;
  std::vector<ITEM*> entries;
  PANEL* panel;
  WINDOW* win;
  WINDOW* subwindow;

  MENU* menu;
  bool shown;
};

bool isSuffix(const std::string& str, const std::string& suffix);

void LevelSelect::Private::readLevelsList() {
  static const std::string ext(".hml");

  SPtr<Config> conf = core.getConfig();
  std::vector<DirEntry> files = listFiles(conf->getLevelsPath());

  for (auto it = files.begin(); it != files.end(); ++it) {
    if (!it->isDir && isSuffix(it->name, ext))
      levelNames.push_back(it->name.substr(0,it->name.size() - ext.size()));
  }
}

void LevelSelect::Private::createWindow() {
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

void LevelSelect::Private::createMenu() {
  readLevelsList();

  for (auto it = levelNames.begin(); it != levelNames.end(); ++it) {
    ITEM* t = new_item(it->c_str(), NULL);
    entries.push_back(t);
  }
  entries.push_back(NULL);

  menu = new_menu(entries.data());

  set_menu_win(menu, win);
  set_menu_sub(menu, subwindow);

  post_menu(menu);
}

void LevelSelect::Private::selectItem(int idx) {

}

LevelSelect::LevelSelect(Game& core) : d(new Private(core)) {
  d->createWindow();
  d->createMenu();
  d->shown = false;
}

LevelSelect::~LevelSelect() {
  hide_panel(d->panel); // Delete from the screen stack.

  unpost_menu(d->menu);
  free_menu(d->menu);

  delwin(d->subwindow);
  delwin(d->win);
  del_panel(d->panel);

  for (size_t i = 0; i < d->entries.size(); ++i)
    free_item(d->entries[i]);
}

void LevelSelect::setMode(enum Mode mode) {
  d->mode = mode;
}

void LevelSelect::handleInput(int kbdIn) {
  ITEM* curItem;

  switch (kbdIn) {
  case UP_CODE:
    menu_driver(d->menu, REQ_UP_ITEM);
    break;
  case DOWN_CODE:
    menu_driver(d->menu, REQ_DOWN_ITEM);
    break;
  case BACKSPACE_CODE:
    d->core.getUI()->switchScreen(UI::MainMenuScreen);
    break;
  case ENTER_CODE:
    curItem = current_item(d->menu);
    d->selectItem(item_index(curItem));
    break;
  default:
    break;
  };
}

void LevelSelect::draw() {
  if (!d->shown) {
    top_panel(d->panel);
    d->shown = true;
  }
}

void LevelSelect::erase() {
  if (d->shown) {
    bottom_panel(d->panel);
    d->shown = false;
  }
}

bool isSuffix(const std::string& str, const std::string& suffix) {
  for (size_t i = 1; i < suffix.size(); ++i) {
    if (str[str.size() - i] != suffix[suffix.size() - i])
      return false;
  }

  return true;
}
