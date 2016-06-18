#ifndef GAME_HPP
#define GAME_HPP

#include "commons.hpp"

class Config;
class Level;
class ObjectContainer;
class UI;

class Game {
public:
  Game();

  Game(const Game&) = delete;
  Game& operator =(const Game&) = delete;

  ~Game();

  /// Advance by one tick.
  void update();

  bool isRunning() const;
  void quit();

  // Component access
  SPtr<Config> getConfig();
  const SPtr<Config> getConfig() const;

  SPtr<Level> getLevel();
  const SPtr<Level> getLevel() const;

  SPtr<ObjectContainer> getObjects();
  const SPtr<ObjectContainer> getObjects() const;

  SPtr<UI> getUI();
  const SPtr<UI> getUI() const;
private:
  class Private;
  UPtr<Private> d;
};

#endif
