#include <curses.h>
#include "Config.hpp"
#include "Game.hpp"
#include "KeyboardInput.hpp"

class KeyboardInput::Private {
public:
  Private(Game& c) : core(c), lastCmd(InputMethod::NoCommand) {};

  Game& core;

  enum InputMethod::Command lastCmd;
};

KeyboardInput::KeyboardInput(int tgtId, Game& core) : InputMethod(tgtId),
    d(new Private(core)) {}

KeyboardInput::~KeyboardInput() {}

enum InputMethod::Command KeyboardInput::getNextCommand() {
  auto res = d->lastCmd;
  d->lastCmd = InputMethod::NoCommand;
  return res; 
}

void KeyboardInput::update() {
  SPtr<Config> conf = d->core.getConfig();

  // Peek at character.
  int in = getch();
  ungetch(in);

  d->lastCmd = conf->getKbdCommand(target, in);
}