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

  // Gameplay methods.
  // Explode everything in line from start to end or
  // until the first non-explodable cell. If start and
  // end are not on horizontal or vertical line -- fails.
  bool explode(const Point& start, const Point& end);
private:
  class Private;
  UPtr<Private> d;
};

#endif
