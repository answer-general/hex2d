#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "commons.hpp"

class Game;

class Engine {
public:
  enum Mode {
    ModeSingle,
    ModeHotseat,
    ModeMulti
  };

  Engine(Game& core);

  Engine(const Engine&) = delete;
  Engine& operator =(const Engine&) = delete;

  ~Engine();

  bool isRunning() const;

  void run();
  void stop();
  void restart();

  void update();

  // Settings for simulation.
  enum Mode getMode() const;
  void setMode(enum Mode);
private:
  class Private;
  UPtr<Private> d;
};

#endif
