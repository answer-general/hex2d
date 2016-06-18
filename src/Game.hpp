#ifndef GAME_HPP
#define GAME_HPP

#include "commons.hpp"

class Config;
class Level;
class ObjectContainer;
class UI;

class Game {
public:
  enum State {
    SimulationStopped, // In menus, not running.
    SimulationRunning, // In game.
    GameStopped // Requested to finish.
  };

  Game();

  Game(const Game&) = delete;
  Game& operator =(const Game&) = delete;

  ~Game();

  bool isRunning() const;

  /// Advance by one tick.
  void update();

  void setState(enum State);

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
