#include <fstream>
#include <ctype.h>
#include <string>
#include "Config.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "InputMethod.hpp"

class Config::Private {
public:
  Private(Game& core) : core(core) {};
  bool loadControls();

  Game& core;

  std::string resDir;
  int codeP1Up;
  int codeP1Right;
  int codeP1Down;
  int codeP1Left;
  int codeP1Plant;

  int codeP2Up;
  int codeP2Right;
  int codeP2Down;
  int codeP2Left;
  int codeP2Plant;
};


Config::Config(Game& c) : d(new Private(c)) {
  char* home = getenv("HOME"); // Don't need to free -- system-allocated.
  d->resDir = home;
  d->resDir += "/.config/HexedMan";

  d->loadControls();
}

Config::~Config() {}

std::string Config::getLevelsPath() const {
  return d->resDir + "/levels/";
}

enum InputMethod::Command Config::getKbdCommand(int playerId, int key) {
  enum InputMethod::Command res;

  key = tolower(key);

  if (playerId == d->core.getPlayer1Id()) {
    if (key == d->codeP1Up) {
      res = InputMethod::MoveUp;
    } else if (key == d->codeP1Left) {
      res = InputMethod::MoveLeft;
    } else if (key == d->codeP1Right) {
      res = InputMethod::MoveRight;
    } else if (key == d->codeP1Down) {
      res = InputMethod::MoveDown;
    } else if (key == d->codeP1Plant) {
      res = InputMethod::BombPlant;
    } else {
      res = InputMethod::NoCommand;
    }
  } else if (playerId == d->core.getPlayer2Id()) {
    if (key == d->codeP2Up) {
      res = InputMethod::MoveUp;
    } else if (key == d->codeP2Left) {
      res = InputMethod::MoveLeft;
    } else if (key == d->codeP2Right) {
      res = InputMethod::MoveRight;
    } else if (key == d->codeP2Down) {
      res = InputMethod::MoveDown;
    } else if (key == d->codeP2Plant) {
      res = InputMethod::BombPlant;
    } else {
      res = InputMethod::NoCommand;
    }
  } else {
    res = InputMethod::NoCommand; // Key not recognized, do nothing.
  }

  return res;
}

bool Config::Private::loadControls() {
  std::string name = resDir + "/binds";

  std::ifstream binds(name.c_str());

  // Load defaults.
  codeP1Up = 'w';
  codeP1Right = 'd';
  codeP1Down = 's';
  codeP1Left = 'a';
  codeP1Plant = 'v';

  codeP2Up = 'i';
  codeP2Right = 'l';
  codeP2Down = 'k';
  codeP2Left = 'j';
  codeP2Plant = '/';

  if (binds.is_open()) {
    std::string name;
    std::string val;
    while (binds.good()) {
      binds >> name >> val;
      if (name == "Player1.Up") {
        codeP1Up = tolower(val[0]);
      } else if (name == "Player1.Right") {
        codeP1Right = tolower(val[0]);
      } else if (name == "Player1.Down") {
        codeP1Down = tolower(val[0]);
      } else if (name == "Player1.Left") {
        codeP1Left = tolower(val[0]);
      } else if (name == "Player1.Plant") {
        codeP1Plant = tolower(val[0]);
      } else if (name == "Player2.Up") {
        codeP2Up = tolower(val[0]);
      } else if (name == "Player2.Right") {
        codeP2Right = tolower(val[0]);
      } else if (name == "Player2.Down") {
        codeP2Down = tolower(val[0]);
      } else if (name == "Player2.Left") {
        codeP2Left = tolower(val[0]);
      } else if (name == "Player2.Plant") {
        codeP2Plant = tolower(val[0]);
      }
    }
  }
  
  if (!binds.eof())
    return false;

  return true;
}
