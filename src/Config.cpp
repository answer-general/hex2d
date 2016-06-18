#include <string>
#include "Config.hpp"
#include "GameObject.hpp"
#include "InputMethod.hpp"

class Config::Private {
public:
  std::string resDir;
};


Config::Config() : d(new Private()) {
  char* home = getenv("HOME"); // Don't need to free -- system-allocated.
  d->resDir = home;
  d->resDir += "/.config/HexedMan";
}

Config::~Config() {}

std::string Config::getLevelsPath() const {
  return d->resDir + "/levels/";
}

enum InputMethod::Command Config::getKbdCommand(int playerId, int key) {
  enum InputMethod::Command res;
  
  if (playerId == GameObject::ActorPlayer1) {
    switch (key) {
    // TODO: replace with configurable bindings.
    case 'W':
    case 'w':
      res = InputMethod::MoveUp;
      break;
    case 'A':
    case 'a':
      res = InputMethod::MoveLeft;
      break;
    case 'D':
    case 'd':
      res = InputMethod::MoveRight;
      break;
    case 'S':
    case 's':
      res = InputMethod::MoveDown;
      break;
    case ' ':
      res = InputMethod::BombPlant;
      break;
    default:
      res = InputMethod::NoCommand;
      break;
    };
  } else {
    res = InputMethod::NoCommand; // Key not recognized, do nothing.
  }

  return res;
}

