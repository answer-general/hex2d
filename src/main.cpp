#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include "Game.hpp"

void init();
void quit(int sig);

int main(void) {
  init();
  signal(SIGINT, quit);

  Game game;

  while (game.isRunning())
    game.update();

  endwin();
  return 0; // Not reached.
}

void init() {
  initscr();
  keypad(stdscr, true); // Enable functional keys.
  cbreak();
  nonl(); // Don't wait for newline.
  nodelay(stdscr, true); // Make getch() non-blocking.
  noecho(); // Disable input echoing.
}

void quit(int sig) {
  endwin();

  if (sig == SIGINT) {
    exit(0);
  }
}
